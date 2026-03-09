cmake_minimum_required(VERSION 3.28)
project(Vec23 VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET "15.0")

include(FetchContent)

# --- GoogleTest ---

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# --- Vec23 ---

add_library(Vec23)

target_sources(Vec23
    PUBLIC
        FILE_SET CXX_MODULES 
        BASE_DIRS include/Vec23
        FILES include/Vec23/Vec23.cppm
    PRIVATE
        include/Vec23/Constants.h
        include/Vec23/Vector2.h
        include/Vec23/Vector3.h
        include/Vec23/Quaternion.h
)

target_include_directories(Vec23 PUBLIC include)

target_compile_features(Vec23 PUBLIC cxx_std_20)

# --- Vec23Test ---

add_executable(Vec23Test
    test/Vector2Test.cpp
    test/Vector3Test.cpp
    test/QuaternionTest.cpp
)

target_link_libraries(Vec23Test PRIVATE 
    GTest::gtest_main
    Vec23
)
