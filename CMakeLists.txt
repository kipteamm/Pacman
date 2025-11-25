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
        Logic/Random.h
        Logic/Stopwatch.h
        Representation/Window.cpp
        Representation/Window.h
        Representation/StateManager.cpp
        Representation/StateManager.h
        Representation/State.cpp
        Representation/State.h
)

target_link_libraries(Pacman PRIVATE sfml-graphics sfml-window sfml-system)