set(UTILITY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# library utility
add_library(utility STATIC "")
target_sources(utility PRIVATE
    ${UTILITY_SOURCE_DIR}/Utils.cc
    ${UTILITY_SOURCE_DIR}/Utils.h
    ${UTILITY_SOURCE_DIR}/Event.cc
    ${UTILITY_SOURCE_DIR}/Event.h
    ${UTILITY_SOURCE_DIR}/EventImpl.cc
    ${UTILITY_SOURCE_DIR}/EventImpl.h
    ${UTILITY_SOURCE_DIR}/Types.h)
target_include_directories(utility PUBLIC ${UTILITY_SOURCE_DIR})
