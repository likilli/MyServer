if (APPLE)
    set(PLATFORM APPLE)
elseif (UNIX)
    set(PLATFORM Linux)
endif()

# gtest
include_directories(${CMAKE_SOURCE_DIR}/deps/gtest/include)
link_directories(${CMAKE_SOURCE_DIR}/deps/gtest/libs/${PLATFORM})


# OpenSSL
include_directories(${CMAKE_SOURCE_DIR}/deps/openssl/include)
link_directories(${CMAKE_SOURCE_DIR}/deps/openssl/libs/${PLATFORM})