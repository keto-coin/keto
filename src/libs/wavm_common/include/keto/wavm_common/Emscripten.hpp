/**
 * This is taken from the WAVM base project.
 */

#pragma once

#ifndef KETO_EMSCRIPTEN_API
#define EMSCRIPTEN_API DLL_IMPORT

#include <vector>

#include "Runtime/Runtime.h"

//namespace IR { struct Module; }
//namespace Runtime { struct ModuleInstance; struct Context; struct Compartment; }

namespace keto {

    namespace Emscripten
    {
            //using namespace Runtime;

            struct Instance
            {
                    Runtime::GCPointer<Runtime::ModuleInstance> env;
                    Runtime::GCPointer<Runtime::ModuleInstance> asm2wasm;
                    Runtime::GCPointer<Runtime::ModuleInstance> global;
                    Runtime::GCPointer<Runtime::ModuleInstance> keto;

                    Runtime::GCPointer<Runtime::MemoryInstance> emscriptenMemory;
            };

            EMSCRIPTEN_API keto::Emscripten::Instance* instantiate(Runtime::Compartment* compartment);
            EMSCRIPTEN_API void initializeGlobals(Runtime::Context* context,const IR::Module& module,Runtime::ModuleInstance* moduleInstance);
            EMSCRIPTEN_API void injectCommandArgs(Emscripten::Instance* instance,const std::vector<const char*>& argStrings,std::vector<Runtime::Value>& outInvokeArgs);
    }
}

#endif
