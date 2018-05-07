/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WavmEngineWrapper.cpp
 * Author: ubuntu
 * 
 * Created on April 9, 2018, 8:46 AM
 */

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

//#include "Programs/CLI.h"
#include "Platform/Platform.h"
#include "Inline/BasicTypes.h"
#include "Inline/Floats.h"
#include "Inline/Timing.h"
#include "keto/wavm_common/Emscripten.hpp"
#include "Inline/BasicTypes.h"
#include "Inline/Timing.h"
#include "IR/Module.h"
#include "IR/Operators.h"
#include "IR/Validate.h"
#include "Runtime/Linker.h"
#include "Runtime/Intrinsics.h"
#include "ThreadTest/ThreadTest.h"
#include "WAST/WAST.h"

#include "keto/wavm_common/WavmEngineWrapper.hpp"
#include "keto/wavm_common/Exception.hpp"


using namespace IR;
using namespace Runtime;



namespace keto {
namespace wavm_common {
    
bool loadTextModule(const std::string& wastString,IR::Module& outModule)
{
    std::vector<WAST::Error> parseErrors;
    WAST::parseModule(wastString.c_str(),wastString.size(),outModule,parseErrors);
    if(!parseErrors.size()) {
        return true; 
    }
    return false;
}


struct RootResolver : Resolver
{
	Compartment* compartment;
	std::map<std::string,ModuleInstance*> moduleNameToInstanceMap;

	RootResolver(Compartment* inCompartment): compartment(inCompartment) {}

	bool resolve(const std::string& moduleName,const std::string& exportName,ObjectType type,Object*& outObject) override
	{
		auto namedInstanceIt = moduleNameToInstanceMap.find(moduleName);
		if(namedInstanceIt != moduleNameToInstanceMap.end())
		{
			outObject = getInstanceExport(namedInstanceIt->second,exportName);
			if(outObject)
			{
				if(isA(outObject,type)) { return true; }
				else
				{
					Log::printf(Log::Category::error,"Resolved import %s.%s to a %s, but was expecting %s",
						moduleName.c_str(),
						exportName.c_str(),
						asString(getObjectType(outObject)).c_str(),
						asString(type).c_str());
					return false;
				}
			}
		}

		Log::printf(Log::Category::error,"Generated stub for missing import %s.%s : %s\n",moduleName.c_str(),exportName.c_str(),asString(type).c_str());
		outObject = getStubObject(type);
		return true;
	}

	Object* getStubObject(ObjectType type) const
	{
		// If the import couldn't be resolved, stub it in.
		switch(type.kind)
		{
		case IR::ObjectKind::function:
		{
			// Generate a function body that just uses the unreachable op to fault if called.
			Serialization::ArrayOutputStream codeStream;
			OperatorEncoderStream encoder(codeStream);
			encoder.unreachable();
			encoder.end();

			// Generate a module for the stub function.
			Module stubModule;
			DisassemblyNames stubModuleNames;
			stubModule.types.push_back(asFunctionType(type));
			stubModule.functions.defs.push_back({{0},{},std::move(codeStream.getBytes()),{}});
			stubModule.exports.push_back({"importStub",IR::ObjectKind::function,0});
			stubModuleNames.functions.push_back({"importStub <" + asString(type) + ">",{},{}});
			IR::setDisassemblyNames(stubModule,stubModuleNames);
			IR::validateDefinitions(stubModule);

			// Instantiate the module and return the stub function instance.
			auto stubModuleInstance = instantiateModule(compartment,stubModule,{});
			return getInstanceExport(stubModuleInstance,"importStub");
		}
		case IR::ObjectKind::memory:
		{
			return asObject(Runtime::createMemory(compartment,asMemoryType(type)));
		}
		case IR::ObjectKind::table:
		{
			return asObject(Runtime::createTable(compartment,asTableType(type)));
		}
		case IR::ObjectKind::global:
		{
			return asObject(Runtime::createGlobal(
				compartment,
				asGlobalType(type),
				Runtime::Value(asGlobalType(type).valueType,Runtime::UntaggedValue())));
		}
		case IR::ObjectKind::exceptionType:
		{
			return asObject(Runtime::createExceptionTypeInstance(asExceptionTypeType(type)));
		}
		default: Errors::unreachable();
		};
	}
};


WavmEngineWrapper::WavmEngineWrapper(const std::string& wast) : wast(wast) {
}


WavmEngineWrapper::~WavmEngineWrapper() {
    
}



void WavmEngineWrapper::execute() {
    Module module;

    // Enable some additional "features" in WAVM that are disabled by default.
    module.featureSpec.importExportMutableGlobals = true;
    module.featureSpec.sharedTables = true;
    // Allow atomics on unshared memories to accomodate atomics on the Emscripten memory.
    module.featureSpec.requireSharedFlagForAtomicOperators = false;

    // Load the module.

    if(!loadTextModule(wast,module)) { 
        BOOST_THROW_EXCEPTION(keto::wavm_common::InvalidContractException());
    }
    // Link the module with the intrinsic modules.
    Compartment* compartment = Runtime::createCompartment();
    Context* context = Runtime::createContext(compartment);
    RootResolver rootResolver(compartment);
    
    std::cout << "Instanciate the server." << std::endl;
    keto::Emscripten::Instance* emscriptenInstance =  keto::Emscripten::instantiate(compartment);
    std::cout << "After getting the instance." << std::endl;
    rootResolver.moduleNameToInstanceMap["env"] = emscriptenInstance->env;
    rootResolver.moduleNameToInstanceMap["asm2wasm"] = emscriptenInstance->asm2wasm;
    rootResolver.moduleNameToInstanceMap["global"] = emscriptenInstance->global;
    rootResolver.moduleNameToInstanceMap["Keto"] = emscriptenInstance->keto;

    LinkResult linkResult = linkModule(module,rootResolver);
    if(!linkResult.success)
    {
        std::stringstream ss;
        ss << "Failed to link module:" << std::endl;
        for(auto& missingImport : linkResult.missingImports)
        {
                ss << "Missing import: module=\"" << missingImport.moduleName
                        << "\" export=\"" << missingImport.exportName
                        << "\" type=\"" << asString(missingImport.type) << "\"" << std::endl;
        }
        BOOST_THROW_EXCEPTION(keto::wavm_common::LinkingFailedException(ss.str()));
    }

    // Instantiate the module.
    ModuleInstance* moduleInstance = instantiateModule(compartment,module,std::move(linkResult.resolvedImports));
    if(!moduleInstance) { BOOST_THROW_EXCEPTION(keto::wavm_common::LinkingFailedException()); }

    // Call the module start function, if it has one.
    FunctionInstance* startFunction = getStartFunction(moduleInstance);
    if(startFunction)
    {
            invokeFunctionChecked(context,startFunction,{});
    }

    keto::Emscripten::initializeGlobals(context,module,moduleInstance);

    // Look up the function export to call.
    FunctionInstance* functionInstance;
    functionInstance = asFunctionNullable(getInstanceExport(moduleInstance,"credit"));
    if(!functionInstance) { functionInstance = asFunctionNullable(getInstanceExport(moduleInstance,"_main")); }
    if(!functionInstance)
    {
        BOOST_THROW_EXCEPTION(keto::wavm_common::MissingEntryPointException());
    }
    const FunctionType* functionType = getFunctionType(functionInstance);

    // Set up the arguments for the invoke.
    std::vector<Value> invokeArgs;
    //Timing::Timer executionTimer;
    Runtime::catchRuntimeExceptions(                                                                                           
        [&]
        {
            Result functionResult = invokeFunctionChecked(context,functionInstance,invokeArgs);
            Runtime::collectGarbage();
        },
        [&](Runtime::Exception&& exception)
        {
            std::stringstream ss;
            ss << "Failed to handle the exception : " << describeException(exception).c_str();
            
            std::cout << ss.str() << std::endl;
            BOOST_THROW_EXCEPTION(keto::wavm_common::ContactExecutionFailedException(ss.str()));
        });
    
}

}
}
