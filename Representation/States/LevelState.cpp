#include "PausedState.h"
#include "LevelState.h"

#include <ranges>

#include "GameOverState.h"
#include "VictoryState.h"
#include "../Camera.h"
#include "../Window.h"


LevelState::LevelState(StateManager& context) : State(context) {
    factory = context.getGameContext().factory;
    factory->setViews(&this->entityViews);

    world = std::make_shared<logic::World>(factory, context.getGameContext().lives);
    world->loadLevel("../Representation/levels/level_1.txt");

    Camera::getInstance().setScaling(world->getWidth(), world->getHeight());

    scoreSystem = context.getGameContext().scoreSystem;
    world->attach(scoreSystem);

    soundManager= context.getGameContext().soundManager;
    soundManager->start();
    world->attach(soundManager);

    worldView = std::make_shared<WorldView>(world, scoreSystem);
    scoreSystem->attach(worldView);
};


void LevelState::update(const double dt) {
    scoreSystem->update(dt);

    for (auto& views : this->entityViews | std::views::values) {
        std::erase_if(views,[](const std::shared_ptr<EntityView>& view) {
            return view->shouldDelete();
        });
    }

    switch (world->update(dt)) {
        case logic::GAME_OVER:
            soundManager->stop();
            this->context.getGameContext().lives = 3;
            this->context.swap(std::make_unique<GameOverState>(this->context));
            return;

        case logic::LEVEL_COMPLETED:
            soundManager->stop();
            this->context.getGameContext().lives = world->getLives();
            this->context.swap(std::make_unique<VictoryState>(this->context));
            return;

        default: return;
    }
}

void LevelState::handleInput(const sf::Event::KeyEvent &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Escape:
            this->context.push(std::make_unique<PausedState>(this->context));
            return;

        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            this->world->handleMove(logic::Moves::UP);
            break;

        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            this->world->handleMove(logic::Moves::LEFT);
            break;

        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            this->world->handleMove(logic::Moves::RIGHT);
            break;

        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            this->world->handleMove(logic::Moves::DOWN);
            break;

        default: break;
    }
}

void LevelState::render() {
    for (const auto& view : this->entityViews[Layer::BACKGROUND]) {
        view->render();
    }

    for (const auto& view : this->entityViews[Layer::FOREGROUND]) {
        view->render();
    }

    for (const auto& view : this->entityViews[Layer::PACMAN]) {
        view->render();
    }

    worldView->render();
}
