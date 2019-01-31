cmake_minimum_required( VERSION 3.10.2 )

project( arkanoid )

find_package( Curses REQUIRED )

set( CMAKE_SOURCE_DIR ${PROJECT_SOURCE_DIR} )
set( CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR} )
set( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} )
set( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR} )

set( CMAKE_CXX_STANDARD 17 )
include_directories( "${PROJECT_SOURCE_DIR}" )
include_directories( "${CURSES_INCLUDE_DIR}" )
link_directories( "${CURSES_INCLUDE_DIR}" )
link_libraries( ${CURSES_LIBRARIES} )
link_libraries( pthread )

if ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)" )
    set( CMAKE_CXX_FLAGS "-O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual" )
endif()

set( TARGET_SOURCES
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/Entity.cpp
    ${CMAKE_SOURCE_DIR}/Block.cpp
    ${CMAKE_SOURCE_DIR}/Paddle.cpp
    ${CMAKE_SOURCE_DIR}/Ball.cpp
    ${CMAKE_SOURCE_DIR}/Map.cpp
)

add_executable( ${PROJECT_NAME} ${TARGET_SOURCES} )
