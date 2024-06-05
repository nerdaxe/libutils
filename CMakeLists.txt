if(ESP_PLATFORM)

idf_component_register(SRCS "src/Utils.cpp" 
                       PRIV_INCLUDE_DIRS include external/etl/include external/spdlog/include 
                       REQUIRES mbedtls)
                       
target_compile_options(${COMPONENT_LIB} PRIVATE -std=gnu++23)

else()
    cmake_minimum_required(VERSION 3.11-3.18)

    project(
        libutils
        VERSION 0.1
        DESCRIPTION "Utils")

    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
    endif() 

    if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_definitions("-DNDEBUG")
    endif()

    #add_library(libutils STATIC src/Stratum.cpp)
    add_definitions("-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG")
    if(NOT TARGET spdlog)
        add_subdirectory(${PROJECT_SOURCE_DIR}/external/spdlog)
    endif()
    include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/external/etl/include ${PROJECT_SOURCE_DIR}/external/spdlog/include)

    add_executable(libutils_test src/test.cpp "src/Utils.cpp")
    add_library(libutils "src/Utils.cpp")

    set_property(TARGET libutils PROPERTY CXX_STANDARD 23)
    set_property(TARGET libutils_test PROPERTY CXX_STANDARD 23)

endif()