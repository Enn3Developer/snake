cmake_minimum_required(VERSION 3.31)
project(snake)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(snake src/main.cpp
        src/engine/Scene.cpp
        src/engine/Engine.cpp
        src/engine/Drawable.cpp
        src/engine/ColorPair.cpp
        src/engine/Actionable.cpp
        src/engine/context/RunContext.cpp
        src/engine/context/InitContext.cpp
        src/engine/context/DrawContext.cpp
        src/engine/components/Label.cpp
        src/engine/components/Button.cpp
        src/game/MainScene.cpp
        src/game/MainScene.h)

target_link_libraries(snake ${CURSES_LIBRARIES})