cmake_minimum_required(VERSION 3.11-3.18)

project(
    libutils
    VERSION 0.1
    DESCRIPTION "Utils")


#add_library(libutils STATIC src/Stratum.cpp)
add_definitions("-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG")
add_subdirectory(${PROJECT_SOURCE_DIR}/external/spdlog)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/external/etl/include ${PROJECT_SOURCE_DIR}/external/spdlog/include)

add_executable(libutils src/test.cpp)

set_property(TARGET libutils PROPERTY CXX_STANDARD 23)