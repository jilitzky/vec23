cmake_minimum_required(VERSION 3.24)

project(Vec23 VERSION 1.0)

set(CMAKE_OSX_DEPLOYMENT_TARGET "15.0")

include(FetchContent)

# --- GoogleTest ---

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF
)
FetchContent_MakeAvailable(googletest)

file(GLOB ALL_HEADERS "include/Vec23/*.h")

# --- Vector23Test ---

add_executable(Vector23Test
    ${ALL_HEADERS}
    test/Vector2Test.cpp
    test/Vector3Test.cpp
    test/QuaternionTest.cpp
)

target_compile_features(Vector23Test PRIVATE cxx_std_17)

target_include_directories(Vector23Test PRIVATE
    include
)

target_link_libraries(Vector23Test PRIVATE 
    GTest::gtest_main
)
