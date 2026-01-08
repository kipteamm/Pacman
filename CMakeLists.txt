cmake_minimum_required(VERSION 3.28)
project(Pacman)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")
#ELSEIF(UNIX)
#    set(SFML_DIR "$ENV{HOME}/SFML-2.6.2/lib/cmake/SFML")
ENDIF(WIN32)

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system audio)

add_subdirectory(Logic)

add_executable(Pacman
        main.cpp
        Representation/Game.cpp
        Representation/Game.h
        Representation/Window.cpp
        Representation/Window.h
        Representation/AssetManager.cpp
        Representation/AssetManager.h
        Representation/Camera.cpp
        Representation/Camera.h
        Representation/SoundManager.cpp
        Representation/SoundManager.h
        Representation/States/StateManager.cpp
        Representation/States/StateManager.h
        Representation/States/MenuState.cpp
        Representation/States/MenuState.h
        Representation/States/LevelState.cpp
        Representation/States/LevelState.h
        Representation/States/PausedState.cpp
        Representation/States/PausedState.h
        Representation/States/GameOverState.cpp
        Representation/States/GameOverState.h
        Representation/States/VictoryState.cpp
        Representation/States/VictoryState.h
        Representation/Entities/ConcreteFactory.cpp
        Representation/Entities/ConcreteFactory.h
        Representation/Entities/EntityView.cpp
        Representation/Entities/EntityView.h
        Representation/Entities/PacmanView.cpp
        Representation/Entities/PacmanView.h
        Representation/Entities/WallView.cpp
        Representation/Entities/WallView.h
        Representation/Entities/CoinView.cpp
        Representation/Entities/CoinView.h
        Representation/Entities/GhostView.cpp
        Representation/Entities/GhostView.h
        Representation/Entities/FruitView.cpp
        Representation/Entities/FruitView.h
        Representation/Entities/WorldView.cpp
        Representation/Entities/WorldView.h
)

target_link_libraries(Pacman PRIVATE Logic sfml-graphics sfml-window sfml-system sfml-audio)