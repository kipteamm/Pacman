Generate with doxygen `doxygen doxygen.txt`

```
Pacman
├─ CMakeLists.txt
├─ Logic
│  ├─ Difficulty.cpp
│  ├─ Difficulty.h
│  ├─ Entities
│  │  ├─ AbstractFactory.h
│  │  ├─ CoinModel.cpp
│  │  ├─ CoinModel.h
│  │  ├─ EntityModel.cpp
│  │  ├─ EntityModel.h
│  │  ├─ FruitModel.cpp
│  │  ├─ FruitModel.h
│  │  ├─ Ghosts
│  │  │  ├─ AmbushGhost.cpp
│  │  │  ├─ AmbushGhost.h
│  │  │  ├─ ChasingGhost.cpp
│  │  │  ├─ ChasingGhost.h
│  │  │  ├─ GhostModel.cpp
│  │  │  ├─ GhostModel.h
│  │  │  ├─ RandomGhost.cpp
│  │  │  └─ RandomGhost.h
│  │  ├─ PacmanModel.cpp
│  │  ├─ PacmanModel.h
│  │  ├─ WallModel.cpp
│  │  └─ WallModel.h
│  ├─ Observer.cpp
│  ├─ Observer.h
│  ├─ Random.cpp
│  ├─ Random.h
│  ├─ Score.cpp
│  ├─ Score.h
│  ├─ Stopwatch.cpp
│  ├─ Stopwatch.h
│  ├─ World.cpp
│  └─ World.h
├─ main.cpp
├─ README.md
└─ Representation
   ├─ AssetManager.cpp
   ├─ AssetManager.h
   ├─ assets
   │  ├─ font.otf
   │  ├─ pacman_logo.png
   │  └─ sprite_sheet.png
   ├─ Camera.cpp
   ├─ Camera.h
   ├─ Entities
   │  ├─ CoinView.cpp
   │  ├─ CoinView.h
   │  ├─ ConcreteFactory.cpp
   │  ├─ ConcreteFactory.h
   │  ├─ EntityView.cpp
   │  ├─ EntityView.h
   │  ├─ FruitView.cpp
   │  ├─ FruitView.h
   │  ├─ GhostView.cpp
   │  ├─ GhostView.h
   │  ├─ PacmanView.cpp
   │  ├─ PacmanView.h
   │  ├─ WallView.cpp
   │  └─ WallView.h
   ├─ Game.cpp
   ├─ Game.h
   ├─ levels
   │  └─ level_1.txt
   ├─ sounds
   │  └─ eatingCoins.flac
   ├─ States
   │  ├─ GameOverState.cpp
   │  ├─ GameOverState.h
   │  ├─ LevelState.cpp
   │  ├─ LevelState.h
   │  ├─ MenuState.cpp
   │  ├─ MenuState.h
   │  ├─ PausedState.cpp
   │  ├─ PausedState.h
   │  ├─ StateManager.cpp
   │  ├─ StateManager.h
   │  ├─ VictoryState.cpp
   │  └─ VictoryState.h
   ├─ Window.cpp
   └─ Window.h

```