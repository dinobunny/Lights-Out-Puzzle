cmake_minimum_required(VERSION 3.14)
project(Lights_Out_Puzzle)

set(CMAKE_CXX_STANDARD 17)

# ================================================================================
# BUILD OPTIONS
# ================================================================================
option(BUILD_TESTING "Build tests" OFF)

# ================================================================================
# Main executable
# ================================================================================
add_executable(Lights_Out_Puzzle main.cpp OpenBox.cpp)

# ================================================================================
# Unit testing setup (optional)
# ================================================================================
if(BUILD_TESTING)
    enable_testing()
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        v1.15.2
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(test_runner
            openbox_test.cpp
            main.cpp
            OpenBox.cpp
            OpenBox.h
            SecureBox.h
    )


    target_compile_definitions(test_runner PRIVATE UNIT_TESTING)

    target_link_libraries(test_runner
            GTest::gtest
            GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(test_runner)
endif()
