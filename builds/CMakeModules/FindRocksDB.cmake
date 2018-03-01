# - Try to find the Botan library
#
# Once done this will define
#
#  ROCKSDB_FOUND - System has RocksDB
#  ROCKSDB_INCLUDE_DIR - The Botan include directory
#  ROCKSDB_LIBRARIES - The libraries needed to use Botan

if (NOT DEFINED ROCKS_ROOT)
  set(ROCKSDB_ROOT_FOLDER $ENV{ROCKSDB_ROOT})
endif()

IF (ROCKSDB_INCLUDE_DIR AND ROCKSDB_LIBRARY)
   # in cache already
   SET(RocksDB_FIND_QUIETLY TRUE)
ENDIF (ROCKSDB_INCLUDE_DIR AND ROCKSDB_LIBRARY)

IF (NOT WIN32)
   # try using pkg-config to get the directories and then use these values
   # in the FIND_PATH() and FIND_LIBRARY() calls
   # also fills in ROCKSDB_DEFINITIONS, although that isn't normally useful
   FIND_PACKAGE(PkgConfig)
   PKG_SEARCH_MODULE(PC_ROCKSDB rocksdb)
   SET(ROCKSDB_DEFINITIONS ${PC_ROCKSDB_CFLAGS})
ENDIF (NOT WIN32)


# attempt to find the botan include directory using the standard KETO build process
# fall back to the installed packages
FIND_PATH(ROCKSDB_INCLUDE_DIR rocksdb/db.h
    PATHS "${ROCKSDB_ROOT_FOLDER}/include/"
)
IF (NOT ROCKSDB_INCLUDE_DIR)
    FIND_PATH(ROCKSDB_INCLUDE_DIR rocksdb/db.h
        HINTS
        ${PC_ROCKSDB_INCLUDEDIR}
        ${PC_ROCKSDB_INCLUDE_DIRS}
        )
ENDIF (NOT ROCKSDB_INCLUDE_DIR)

# find the library, first be optimist and this is being built with a standard KETO build,
# if not found fall back to the possible package install
find_library(ROCKSDB_LIBRARY
    NAMES rocksdb
    PATHS ${ROCKSDB_ROOT_FOLDER}/lib)

IF (NOT ROCKSDB_LIBRARY)
    FIND_LIBRARY(ROCKSDB_LIBRARY NAMES ${PC_ROCKSDB_LIBRARIES}
        HINTS
        ${PC_ROCKSDB_LIBDIR}
        ${PC_ROCKSDB_LIBRARY_DIRS}
        )
ENDIF (NOT ROCKSDB_LIBRARY)

FIND_LIBRARY(ROCKSDB_EXTRA_LIBRARY 
        NAMES
        zstd
        )

message(STATUS "ROCKSDB_INCLUDE_DIR " ${ROCKSDB_INCLUDE_DIR})
message(STATUS "ROCKSDB_LIBRARY " ${ROCKSDB_LIBRARY})
message(STATUS "ROCKSDB_EXTRA_LIBRARY " ${ROCKSDB_EXTRA_LIBRARY})

MARK_AS_ADVANCED(ROCKSDB_INCLUDE_DIR ROCKSDB_LIBRARY ROCKSDB_EXTRA_LIBRARY)

# handle the QUIETLY and REQUIRED arguments and set ROCKSDB_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(RocksDB DEFAULT_MSG ROCKSDB_LIBRARY ROCKSDB_INCLUDE_DIR ROCKSDB_EXTRA_LIBRARY)

IF(ROCKSDB_FOUND)
    SET(ROCKSDB_LIBRARIES    ${ROCKSDB_LIBRARY})
    SET(ROCKSDB_INCLUDE_DIRS ${ROCKSDB_INCLUDE_DIR})
    SET(ROCKSDB_EXTRA_LIBRARY ${ROCKSDB_EXTRA_LIBRARY})
ENDIF()
