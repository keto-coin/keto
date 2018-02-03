# - Try to find the Botan library
#
# Once done this will define
#
#  BOTAN_FOUND - System has Botan
#  BOTAN_INCLUDE_DIR - The Botan include directory
#  BOTAN_LIBRARIES - The libraries needed to use Botan

if (NOT DEFINED BOTAN_ROOT)
  set(BOTAN_ROOT_FOLDER $ENV{BOTAN_ROOT})
endif()

IF (BOTAN_INCLUDE_DIR AND BOTAN_LIBRARY)
   # in cache already
   SET(Botan_FIND_QUIETLY TRUE)
ENDIF (BOTAN_INCLUDE_DIR AND BOTAN_LIBRARY)

IF (NOT WIN32)
   # try using pkg-config to get the directories and then use these values
   # in the FIND_PATH() and FIND_LIBRARY() calls
   # also fills in BOTAN_DEFINITIONS, although that isn't normally useful
   FIND_PACKAGE(PkgConfig)
   PKG_SEARCH_MODULE(PC_BOTAN botan-1.10 botan-1.9 botan-1.8 botan-2 botan)
   SET(BOTAN_DEFINITIONS ${PC_BOTAN_CFLAGS})
ENDIF (NOT WIN32)


# attempt to find the botan include directory using the standard KETO build process
# fall back to the installed packages
FIND_PATH(BOTAN_INCLUDE_DIR botan-2/botan/botan.h
    PATHS "${BOTAN_ROOT_FOLDER}/include"
)
IF (NOT BOTAN_INCLUDE_DIR)
    FIND_PATH(BOTAN_INCLUDE_DIR botan/botan.h
        HINTS
        ${PC_BOTAN_INCLUDEDIR}
        ${PC_BOTAN_INCLUDE_DIRS}
        )
ENDIF (NOT BOTAN_INCLUDE_DIR)

# find the library, first be optimist and this is being built with a standard KETO build,
# if not found fall back to the possible package install
find_library(BOTAN_LIBRARY
    NAMES botan-2
    PATHS ${BOTAN_ROOT_FOLDER}/lib)

IF (NOT BOTAN_LIBRARY)
    FIND_LIBRARY(BOTAN_LIBRARY NAMES ${PC_BOTAN_LIBRARIES}
        HINTS
        ${PC_BOTAN_LIBDIR}
        ${PC_BOTAN_LIBRARY_DIRS}
        )
ENDIF (NOT BOTAN_LIBRARY)

message(STATUS "BOTAN_INCLUDE_DIR " ${BOTAN_INCLUDE_DIR})
message(STATUS "BOTAN_LIBRARY " ${BOTAN_LIBRARY})

MARK_AS_ADVANCED(BOTAN_INCLUDE_DIR BOTAN_LIBRARY)

# handle the QUIETLY and REQUIRED arguments and set BOTAN_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Botan DEFAULT_MSG BOTAN_LIBRARY BOTAN_INCLUDE_DIR)

IF(BOTAN_FOUND)
    SET(BOTAN_LIBRARIES    ${BOTAN_LIBRARY})
    SET(BOTAN_INCLUDE_DIRS ${BOTAN_INCLUDE_DIR})
ENDIF()
