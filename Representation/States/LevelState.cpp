#include "PausedState.h"
#include "LevelState.h"

#include "GameOverState.h"
#include "VictoryState.h"
#include "../AssetManager.h"
#include "../Window.h"


LevelState::LevelState(StateManager *context, const std::shared_ptr<ConcreteFactory>& factory, const std::shared_ptr<logic::Score>& scoreSystem) : State(context), factory(factory), scoreSystem(scoreSystem) {
    factory->setViews(&this->entityViews);

    world = std::make_unique<logic::World>(factory);
    world->loadLevel("../Representation/levels/level_1.txt");
    world->attach(scoreSystem);

    Camera::getInstance().setScaling(world->getWidth(), world->getHeight());

    live1.setTexture(AssetManager::getInstance().getSpriteSheet());
    live2.setTexture(AssetManager::getInstance().getSpriteSheet());
    live3.setTexture(AssetManager::getInstance().getSpriteSheet());

    live1.setTextureRect({16, 0, 16, 16});
    live2.setTextureRect({16, 0, 16, 16});
    live3.setTextureRect({16, 0, 16, 16});

    const float scaleX = Camera::getInstance().getTileWidth() / 16.0f;
    const float scaleY = Camera::getInstance().getTileHeight() / 16.0f;

    live1.setScale(scaleX, scaleY);
    live2.setScale(scaleX, scaleY);
    live3.setScale(scaleX, scaleY);

    const float mapLeftPixel = Camera::getInstance().xToPixel(-1.0f);
    const float mapRightPixel = Camera::getInstance().xToPixel(1.0f);
    const float uiYPosition = Camera::getInstance().yToPixel(1.0f) + 10.0f;

    const float spriteWidth = 16.0f * scaleX;
    const float gap = 4.0f * scaleX;

    // TODO: fix resizing
    live1.setPosition(mapLeftPixel, uiYPosition);
    live2.setPosition(mapLeftPixel + spriteWidth + gap, uiYPosition);
    live3.setPosition(mapLeftPixel + (spriteWidth + gap) * 2, uiYPosition);

    scoreText.setFont(AssetManager::getInstance().getFont());
    scoreText.setString("0     ");
    scoreText.setCharacterSize(static_cast<unsigned int>(16 * scaleY));
    scoreText.setFillColor(sf::Color::White);

    const sf::FloatRect textBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(textBounds.width, 0);
    scoreText.setPosition(mapRightPixel, uiYPosition);
};


void LevelState::update(const double dt) {
    scoreSystem->update(dt);
    scoreText.setString(std::to_string(scoreSystem->getScore()));

    for (auto& [_, views] : this->entityViews) {
        std::erase_if(views,[](const std::shared_ptr<EntityView>& view) {
            return view->shouldDelete();
        });
    }

    switch (world->update(dt)) {
        case logic::GAME_OVER:
            this->context->swap(std::make_unique<GameOverState>(this->context, factory, scoreSystem));
            return;

        case logic::LEVEL_COMPLETED:
            this->context->swap(std::make_unique<VictoryState>(this->context, factory, scoreSystem));
            return;

        default: return;
    }
}

void LevelState::handleInput(const sf::Event::KeyEvent &keyPressed) {
    switch (keyPressed.code) {
        case sf::Keyboard::Escape:
            this->context->push(std::make_unique<PausedState>(this->context));
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

    const unsigned int lives = world->getLives();
    if (lives > 0) Window::getInstance().draw(live1);
    if (lives > 1) Window::getInstance().draw(live2);
    if (lives > 2) Window::getInstance().draw(live3);

    Window::getInstance().draw(scoreText);
}
