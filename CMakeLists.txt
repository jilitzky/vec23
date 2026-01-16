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

file(GLOB ALL_HEADERS "include/*.h")

# --- Vector2Test ---

add_executable(Vector2Test
    ${ALL_HEADERS}
    test/Vector2Test.cpp 
)

target_compile_features(Vector2Test PRIVATE cxx_std_17)

target_include_directories(Vector2Test PRIVATE
    include
)

target_link_libraries(Vector2Test PRIVATE 
    GTest::gtest_main
)
