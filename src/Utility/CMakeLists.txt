set(UTILITY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# library utility
add_library(utility STATIC "")
target_sources(utility PRIVATE
    ${UTILITY_SOURCE_DIR}/Event.cpp
    ${UTILITY_SOURCE_DIR}/Event.hpp
    ${UTILITY_SOURCE_DIR}/EventImpl.cpp
    ${UTILITY_SOURCE_DIR}/EventImpl.hpp
    ${UTILITY_SOURCE_DIR}/Core.hpp)
target_include_directories(utility PUBLIC ${UTILITY_SOURCE_DIR})
