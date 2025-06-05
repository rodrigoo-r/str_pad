include(FetchContent)
cmake_minimum_required(VERSION 3.12)
project(str_pad C)

set(CMAKE_C_STANDARD 11)

add_library(str_pad STATIC str_pad.c str_pad.h)

if(NOT FLUENT_LIBC_RELEASE)
    FetchContent_Declare(
            string_builder
            GIT_REPOSITORY https://github.com/rodrigoo-r/string_builder
            GIT_TAG        master
    )

    FetchContent_Declare(
            types
            GIT_REPOSITORY https://github.com/rodrigoo-r/types
            GIT_TAG        master
    )

    FetchContent_MakeAvailable(string_builder)
    FetchContent_MakeAvailable(types)

    target_include_directories(str_pad PRIVATE ${CMAKE_BINARY_DIR}/_deps/string_builder-src)
    target_link_libraries(str_pad PRIVATE string_builder)

    target_include_directories(str_pad PRIVATE ${CMAKE_BINARY_DIR}/_deps/types-src)
    target_link_libraries(str_pad PRIVATE types)
endif()