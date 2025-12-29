#include <ranges>

#include "GameOverState.h"
#include "VictoryState.h"
#include "PausedState.h"
#include "LevelState.h"
#include "../Camera.h"
#include "../Window.h"


LevelState::LevelState(StateManager& context) : State(context), cleanupRequired(true) {
    // Creata a factory object and pass along the entityViews of this State.
    // The factory appends the Views to their respective layers.
    factory = std::make_unique<ConcreteFactory>(this->entityViews);
    world = std::make_shared<logic::World>(factory, context.getGameContext().lives);

    // Update the Camera to be aware of the size of the world and scale
    // appropriately.
    world->loadLevel("../Representation/levels/level_1.txt");
    Camera::getInstance().setScaling(world->getWidth(), world->getHeight());

    scoreSystem = context.getGameContext().scoreSystem;
    world->attach(scoreSystem);

    soundManager= context.getGameContext().soundManager;
    soundManager->start();
    world->attach(soundManager);

    worldView = std::make_shared<WorldView>(world, scoreSystem);
    scoreSystem->attach(worldView);

    // Make LevelState an Observer of the World
    world->attach(std::shared_ptr<Observer>(this));
};


void LevelState::update(const logic::Events event) {
    switch (event) {
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

        case logic::COIN_EATEN:
        case logic::FRUIT_EATEN:
            cleanupRequired = true;
            return;

        default: return;
    }
}


void LevelState::update(const double dt) {
    // Update the ScoreSystem (for score decay)
    scoreSystem->update(dt);

    world->update(dt);

    // Only try to remove deleted entities when we know from an Observed event
    // that at least one entity should be deleted.
    if (!cleanupRequired) return;

    // Will delete any entities which were notified to delete themselves after
    // their Model was deleted by the World. Is called at the end of the update
    // loop assuring the World update has finished.
    for (auto& views : this->entityViews | std::views::values) {
        std::erase_if(views,[](const std::shared_ptr<EntityView>& view) {
            return view->shouldDelete();
        });
    }

    cleanupRequired = false;
}

void LevelState::handleInput(const sf::Event::KeyEvent &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Escape:
            // Pushing a new state to the stack top, means that the PausedState
            // update function will be called, and no longer the one of this
            // LevelState, ensuring that the World no longer receives updates
            // while paused. Pushing is done and not swapping because the
            // LevelState (and thus the World) must be preserved while paused.
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
    // Render based on layers, assuring certain things are always on top of
    // other things. UI will always be rendered last, overlaying anything.

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
