add_library(Logic STATIC
        Stopwatch.cpp
        Stopwatch.h
        Score.cpp
        Score.h
        Observer.cpp
        Observer.h
        World.cpp
        World.h
        Random.cpp
        Random.h
        Difficulty.cpp
        Difficulty.h
        Entities/AbstractFactory.h
        Entities/EntityModel.cpp
        Entities/EntityModel.h
        Entities/PacmanModel.cpp
        Entities/PacmanModel.h
        Entities/WallModel.cpp
        Entities/WallModel.h
        Entities/CoinModel.cpp
        Entities/CoinModel.h
        Entities/FruitModel.cpp
        Entities/FruitModel.h
        Entities/Ghosts/GhostModel.cpp
        Entities/Ghosts/GhostModel.h
        Entities/Ghosts/ChasingGhost.cpp
        Entities/Ghosts/ChasingGhost.h
        Entities/Ghosts/AmbushGhost.cpp
        Entities/Ghosts/AmbushGhost.h
        Entities/Ghosts/RandomGhost.cpp
        Entities/Ghosts/RandomGhost.h
        Entities/Ghosts/GhostNavigator.cpp
        Entities/Ghosts/GhostNavigator.h
)

target_include_directories(Logic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})