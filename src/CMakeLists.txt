cmake_minimum_required(VERSION 3.12)
project(arkanoid CXX)

find_package(Curses REQUIRED)
find_package(Threads REQUIRED)

include_directories("${CURSES_INCLUDE_DIR}")
link_directories("${CURSES_INCLUDE_DIR}")

set(SOURCE_FILES main.cpp
        ball.cpp
        block.cpp
        entity.cpp
        map.cpp
        paddle.cpp
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE project_warnings Threads::Threads ${CURSES_LIBRARIES})
