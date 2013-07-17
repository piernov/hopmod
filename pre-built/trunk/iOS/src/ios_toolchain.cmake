include(CMakeForceCompiler)

message("building with iOS toolchain")

set(CMAKE_CROSSCOMPILING   TRUE)
set(CMAKE_SYSTEM_NAME      "Darwin")
set(CMAKE_SYSTEM_PROCESSOR "arm")

set(LIBROOT    "/home/thomas/ios/libs")
set(CC         "ios-clang")
set(CXX        "ios-clang++")
set(AR         "arm-apple-darwin11-ar")
set(RANLIB     "arm-apple-darwin11-ranlib")

set(ARCH       "-arch armv7s -arch armv7 -arch armv6")

set(CMAKE_EXE_LINKER_FLAGS      ${ARCH})
set(CMAKE_MODULE_LINKER_FLAGS   ${ARCH})
set(CMAKE_SHARED_LINKER_FLAGS   ${ARCH})

link_directories("${LIBROOT}/lib")
include_directories("${LIBROOT}/include")

CMAKE_FORCE_C_COMPILER         (${CC} clang)
CMAKE_FORCE_CXX_COMPILER       (${CXX} clang)
set(CMAKE_RANLIB ${RANLIB})

set(CMAKE_CXX_ARCHIVE_CREATE   "${AR} rc <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_CREATE     "${AR} rc <TARGET> <LINK_FLAGS> <OBJECTS>")

set(CMAKE_C_COMPILE_OBJECT     "${CC} ${ARCH} <FLAGS> <DEFINES> -c <SOURCE> -o <OBJECT>")
set(CMAKE_CXX_COMPILE_OBJECT   "${CXX} ${ARCH} <FLAGS> <DEFINES> -c <SOURCE> -o <OBJECT>")

set(CMAKE_C_LINK_EXECUTABLE    "${CC} ${ARCH} <FLAGS> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_CXX_LINK_EXECUTABLE  "${CXX} ${ARCH} <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

set(CMAKE_CXX_ARCHIVE_FINISH   "${RANLIB} <TARGET>")
set(CMAKE_C_ARCHIVE_FINISH     "${RANLIB} <TARGET>")

set(CMAKE_FIND_ROOT_PATH ${LIBROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM  NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY  ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE  ONLY)