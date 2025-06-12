cmake_minimum_required(VERSION 3.31)
project(snake)

set(CMAKE_CXX_FLAGS_RELEASE "-Os -s")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
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
        src/game/scenes/MainScene.cpp
        src/game/scenes/MainScene.h
        src/engine/File.cpp
        src/engine/File.h
        src/game/components/Snake.cpp
        src/game/components/Snake.h
        src/engine/components/Scrollable.cpp
        src/engine/components/Scrollable.h
        src/game/scenes/LeaderboardScene.cpp
        src/game/scenes/LeaderboardScene.h
        src/game/scenes/GameScene.cpp
        src/game/scenes/GameScene.h
        src/engine/components/Modal.cpp
        src/engine/components/Modal.h
        src/game/Score.cpp
        src/game/Score.h
        src/engine/components/Alert.cpp
        src/engine/components/Alert.h
        src/game/scenes/LevelSelectionScene.cpp
        src/game/scenes/LevelSelectionScene.h)

target_link_libraries(snake ${CURSES_LIBRARIES})