#include "PausedState.h"
#include "LevelState.h"


LevelState::LevelState(StateManager *context) : State(context) {
    factory = std::make_shared<ConcreteFactory>(entityViews);

    world = std::make_unique<logic::World>(factory);
    world->loadLevel("../Representation/levels/level_1.txt");
};


void LevelState::update(const double dt) {
    world->update(dt);
}

void LevelState::handleInput(const sf::Event::KeyEvent &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Escape:
            this->context->swap(std::make_unique<PausedState>(this->context));
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
    for (const auto& view : entityViews) {
        view->draw();
    }
}
