cmake_minimum_required(VERSION 3.30)
project(Pacman)

set(CMAKE_CXX_STANDARD 23)

IF(WIN32)
    set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")
ELSEIF(UNIX)
    # Do linux specific includes
ENDIF(WIN32)

find_package(SFML 2.6.2 REQUIRED COMPONENTS graphics window system)

add_executable(Pacman main.cpp
        Representation/Game.cpp
        Representation/Game.h
        Logic/Stopwatch.h
        Representation/Window.cpp
        Representation/Window.h
        Logic/Score.cpp
        Logic/Score.h
        Logic/Observer.h
        Logic/Observer.cpp
        Representation/AssetManager.cpp
        Representation/AssetManager.h
        Representation/States/MenuState.cpp
        Representation/States/MenuState.h
        Representation/States/StateManager.h
        Representation/States/StateManager.cpp
        Representation/States/LevelState.cpp
        Representation/States/LevelState.h
        Logic/Entities/AbstractFactory.h
        Logic/Entities/EntityModel.cpp
        Logic/Entities/EntityModel.h
        Representation/Entities/ConcreteFactory.cpp
        Representation/Entities/ConcreteFactory.h
        Logic/World.cpp
        Logic/World.h
        Representation/States/PausedState.cpp
        Representation/States/PausedState.h
        Representation/Entities/EntityView.cpp
        Representation/Entities/EntityView.h
        Logic/Stopwatch.cpp
        Logic/Entities/PacManModel.cpp
        Logic/Entities/PacManModel.h
        Representation/Entities/PacManView.cpp
        Representation/Entities/PacManView.h
        Representation/Camera.cpp
        Representation/Camera.h
        Logic/Entities/WallModel.cpp
        Logic/Entities/WallModel.h
        Representation/Entities/WallView.cpp
        Representation/Entities/WallView.h
        Representation/Entities/CoinView.cpp
        Representation/Entities/CoinView.h
        Logic/Entities/CoinModel.cpp
        Logic/Entities/CoinModel.h
        Logic/Entities/Ghosts/GhostModel.cpp
        Logic/Entities/Ghosts/GhostModel.h
        Representation/Entities/GhostView.cpp
        Representation/Entities/GhostView.h
        Logic/Entities/Ghosts/ChasingGhost.cpp
        Logic/Entities/Ghosts/ChasingGhost.h
        Logic/Entities/Ghosts/AmbushGhost.cpp
        Logic/Entities/Ghosts/AmbushGhost.h
        Logic/Entities/Ghosts/RandomGhost.cpp
        Logic/Entities/Ghosts/RandomGhost.h
        Logic/Random.cpp
        Logic/Random.h
        Representation/States/GameOverState.cpp
        Representation/States/GameOverState.h
        Logic/Entities/FruitModel.cpp
        Logic/Entities/FruitModel.h
        Representation/Entities/FruitView.cpp
        Representation/Entities/FruitView.h
)

target_link_libraries(Pacman PRIVATE sfml-graphics sfml-window sfml-system)