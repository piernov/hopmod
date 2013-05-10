include(CMakeForceCompiler)

message("building hopmod with iOS toolchain")

set(CMAKE_CROSSCOMPILING   TRUE)
set(CMAKE_SYSTEM_NAME      "Darwin")
set(CMAKE_SYSTEM_PROCESSOR "arm")

set(LIBROOT    "/home/thomas/ios/libs")
set(CC         "ios-clang")
set(CXX        "ios-clang++")
set(AR         "/usr/bin/arm-apple-darwin11-ar")
set(RANLIB     "/usr/bin/arm-apple-darwin11-ranlib")

set(ARCH       "-arch armv7 -arch armv6")

set(CMAKE_EXE_LINKER_FLAGS "${ARCH}")

set(CMAKE_C_FLAGS          "${ARCH}")
set(CMAKE_CXX_FLAGS        "${ARCH}")

link_directories("${LIBROOT}/lib")
include_directories("${LIBROOT}/include")

CMAKE_FORCE_C_COMPILER          (${CC} clang)
CMAKE_FORCE_CXX_COMPILER        (${CXX} clang)

set(CMAKE_CXX_ARCHIVE_CREATE "${AR} rc <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_CREATE   "${AR} rc <TARGET> <LINK_FLAGS> <OBJECTS>")

set(CMAKE_CXX_ARCHIVE_FINISH "${RANLIB} <TARGET>")
set(CMAKE_C_ARCHIVE_FINISH   "${RANLIB} <TARGET>")

set(CMAKE_FIND_ROOT_PATH               "${LIBROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM  NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY  ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE  ONLY)
