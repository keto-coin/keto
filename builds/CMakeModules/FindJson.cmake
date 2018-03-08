# - Try to find the Botan library
#
# Once done this will define
#
#  JSON_FOUND - System has Botan
#  JSON_INCLUDE_DIR - The Botan include directory

if (NOT DEFINED JSON_ROOT)
  set(JSON_ROOT_FOLDER $ENV{JSON_ROOT})
endif()

IF (JSON_INCLUDE_DIR)
   # in cache already
   SET(Json_FIND_QUIETLY TRUE)
ENDIF (JSON_INCLUDE_DIR)

# attempt to find the botan include directory using the standard KETO build process
# fall back to the installed packages
FIND_PATH(JSON_INCLUDE_DIR nlohmann/json.hpp
    PATHS "${JSON_ROOT_FOLDER}/include/"
)

message(STATUS "JSON_INCLUDE_DIR " ${JSON_INCLUDE_DIR})

MARK_AS_ADVANCED(JSON_INCLUDE_DIR)

# handle the QUIETLY and REQUIRED arguments and set JSON_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Json DEFAULT_MSG JSON_INCLUDE_DIR)

IF(JSON_FOUND)
    SET(JSON_INCLUDE_DIRS ${JSON_INCLUDE_DIR})
ENDIF()
