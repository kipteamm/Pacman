#include <ranges>

#include "GameOverState.h"
#include "VictoryState.h"
#include "PausedState.h"
#include "LevelState.h"
#include "../Camera.h"
#include "../Window.h"


LevelState::LevelState(passkey, StateManager& context) : State(context), cleanupRequired(true) {
    // Creata a factory object and pass along the entityViews of this State.
    // The factory appends the Views to their respective layers.
    factory = std::make_shared<ConcreteFactory>(this->entityViews);
    world = std::make_shared<logic::World>(factory, context.getGameContext().lives);

    // Update the Camera to be aware of the size of the world and scale
    // appropriately.
    world->loadLevel("../Representation/levels/level_1.txt");
    Camera::getInstance().setScaling(world->getWidth(), world->getHeight());
    resizeRequired = true;

    scoreSystem = context.getGameContext().scoreSystem;
    world->attach(scoreSystem);

    soundManager = context.getGameContext().soundManager;
    soundManager->start();
    world->attach(soundManager);

    worldView = std::make_shared<WorldView>(world, scoreSystem);
    scoreSystem->attach(worldView);
    world->attach(worldView);
};


std::shared_ptr<LevelState> LevelState::create(StateManager& context) {
    std::shared_ptr<LevelState> levelState = std::make_shared<LevelState>(passkey{}, context);
    levelState->world->attach(levelState);

    return levelState;
}


void LevelState::update(const logic::Events event) {
    switch (event) {
        case logic::GAME_OVER:
            soundManager->stop();
            this->context.getGameContext().lives = 3;
            this->context.swap(std::make_shared<GameOverState>(this->context));
            return;

        case logic::LEVEL_COMPLETED:
            soundManager->stop();
            this->context.getGameContext().lives = world->getLives();
            this->context.swap(std::make_shared<VictoryState>(this->context));
            return;

        case logic::COIN_EATEN:
        case logic::FRUIT_EATEN:
            cleanupRequired = true;
            return;

        default: return;
    }
}


void LevelState::handleInput(const sf::Event::KeyEvent &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Escape:
            // Pushing a new state to the stack top, means that the PausedState
            // update function will be called, and no longer the one of this
            // LevelState, ensuring that the World no longer receives updates
            // while paused. Pushing is done and not swapping because the
            // LevelState (and thus the World) must be preserved while paused.
            this->context.push(std::make_shared<PausedState>(this->context));
            this->soundManager->stop();
            break;

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


void LevelState::resized() {
    resizeRequired = true;
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


void LevelState::render() {
    // Render based on layers, assuring certain things are always on top of
    // other things. UI will always be rendered last, overlaying anything.

    // Makes use of the resizeRequired boolean which is toggled on when a
    // sf::Resized event is captured. Resizing it in the render function saved
    // me writing an extra loop. Could've instead also done it in
    // LevelState::resized();

    for (const auto& view : this->entityViews[Layer::BACKGROUND]) {
        if (resizeRequired) view->resized();
        view->render();
    }

    for (const auto& view : this->entityViews[Layer::FOREGROUND]) {
        if (resizeRequired) view->resized();
        view->render();
    }

    for (const auto& view : this->entityViews[Layer::PACMAN]) {
        if (resizeRequired) view->resized();
        view->render();
    }

    if (resizeRequired) worldView->resized();
    worldView->render();

    resizeRequired = false;
}
