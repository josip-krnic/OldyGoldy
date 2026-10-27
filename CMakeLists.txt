cmake_minimum_required(VERSION 3.16)

project(OldyGoldy LANGUAGES C CXX)

# C configuration
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# C++ configuration for Google Test
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Collect application source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

# Main application
add_executable(OldyGoldy ${SOURCES})

target_include_directories(OldyGoldy PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

target_link_libraries(OldyGoldy PRIVATE
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
)

# Copy fonts to the executable directory
add_custom_command(TARGET OldyGoldy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/fonts"
        "$<TARGET_FILE_DIR:OldyGoldy>/fonts"
    COMMENT "Copying fonts directory"
)

# Google Test configuration
include(CTest)

if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    FetchContent_MakeAvailable(googletest)

    include(GoogleTest)

    # Find immediate subdirectories inside tests/
    file(GLOB TEST_SUBDIRS LIST_DIRECTORIES true
        "${CMAKE_SOURCE_DIR}/tests/*"
    )

    foreach(TEST_DIR ${TEST_SUBDIRS})
        if(IS_DIRECTORY "${TEST_DIR}")
            # Use the subfolder name as the executable name
            get_filename_component(TEST_NAME "${TEST_DIR}" NAME)

            # Find all .cpp files recursively in this subfolder
            file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
                "${TEST_DIR}/*.cpp"
            )

            # Create an executable only if test files exist
            if(TEST_SOURCES)
                add_executable(${TEST_NAME} ${TEST_SOURCES})

                # Output test executables to build/test/
                set_target_properties(${TEST_NAME} PROPERTIES
                    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
                )

                target_include_directories(${TEST_NAME} PRIVATE
                    "${CMAKE_SOURCE_DIR}/include"
                )

                target_link_libraries(${TEST_NAME} PRIVATE
                    GTest::gtest_main
                )

                # Register individual test cases with CTest
                gtest_discover_tests(${TEST_NAME})
            endif()
        endif()
    endforeach()
endif()
