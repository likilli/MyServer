if (APPLE)
    set(PLATFORM APPLE)
	message(STATUS "[Platform]: Apple")
elseif (UNIX)
    set(PLATFORM Linux)
	message(STATUS "[Platfrom]: Linux")
endif()

# gtest
include_directories(${CMAKE_SOURCE_DIR}/deps/gtest/include)
link_directories(${CMAKE_SOURCE_DIR}/deps/gtest/libs/${PLATFORM})

if (USE_LIBEVENT)
	include_directories(${CMAKE_SOURCE_DIR}/deps/libevent/include)
	include_directories(${CMAKE_SOURCE_DIR}/deps/libevent/include/event2)
	link_directories(${CMAKE_SOURCE_DIR}/deps/libevent/libs/${PLATFORM})
endif()
