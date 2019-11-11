cmake_minimum_required(VERSION 3.12)
project(arkanoid CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories("include")

add_library(project_warnings INTERFACE)

if (MSVC)
    target_compile_options(project_warnings INTERFACE /W4)
else()
    target_compile_options(project_warnings
                         INTERFACE
#                         -Werror
                         -Wall
                         -Wextra
                         -Wshadow
                         -Wnon-virtual-dtor
                         -Wold-style-cast
                         -Wcast-align
                         -Wunused
                         -Woverloaded-virtual
                         -Wpedantic
                         -Wconversion
                         -Wsign-conversion
                         -Wmisleading-indentation
                         -Wduplicated-cond
                         -Wduplicated-branches
                         -Wlogical-op
                         -Wnull-dereference
                         -Wuseless-cast
                         -Wdouble-promotion
                         -Wformat=2
                         )
endif()

add_subdirectory(src)
