#include "../AssetManager.h"
#include "../Camera.h"
#include "../Window.h"
#include "WorldView.h"


WorldView::WorldView(const std::shared_ptr<logic::World>& world, const std::shared_ptr<logic::Score>& scoreSystem) : world(world), scoreSystem(scoreSystem) {
    live1.setTexture(AssetManager::getInstance().getSpriteSheet());
    live2.setTexture(AssetManager::getInstance().getSpriteSheet());
    live3.setTexture(AssetManager::getInstance().getSpriteSheet());

    live1.setTextureRect({16, 0, 16, 16});
    live2.setTextureRect({16, 0, 16, 16});
    live3.setTextureRect({16, 0, 16, 16});

    this->resized();
}


void WorldView::update(const logic::Events event) {
    if (event != logic::Events::SCORE_UPDATE) return;
    scoreText.setString(std::to_string(scoreSystem->getScore()));
}


void WorldView::resized() {
    const float scaleX = Camera::getInstance().getTileWidth() / 16.0f;
    const float scaleY = Camera::getInstance().getTileHeight() / 16.0f;

    live1.setScale(scaleX, scaleY);
    live2.setScale(scaleX, scaleY);
    live3.setScale(scaleX, scaleY);

    const float spriteWidth = 16.0f * scaleX;
    const float gap = 4.0f * scaleX;

    const float mapLeftPixel = Camera::getInstance().xToPixel(-1.0f);
    const float mapRightPixel = Camera::getInstance().xToPixel(1.0f);
    const float uiYPosition = Camera::getInstance().yToPixel(1.0f) + 10.0f - gap;

    live1.setPosition(mapLeftPixel, uiYPosition);
    live2.setPosition(mapLeftPixel + spriteWidth + gap, uiYPosition);
    live3.setPosition(mapLeftPixel + (spriteWidth + gap) * 2, uiYPosition);

    scoreText.setFont(AssetManager::getInstance().getFont());
    scoreText.setString("0     ");
    scoreText.setCharacterSize(static_cast<unsigned int>(16 * scaleY));
    scoreText.setFillColor(sf::Color::White);

    scoreText.setOrigin(scoreText.getLocalBounds().width, 0);
    scoreText.setPosition(mapRightPixel, uiYPosition - (gap / 2));
}


void WorldView::render() const {
    const unsigned int lives = world->getLives();
    if (lives > 0) Window::getInstance().draw(live1);
    if (lives > 1) Window::getInstance().draw(live2);
    if (lives > 2) Window::getInstance().draw(live3);

    Window::getInstance().draw(scoreText);
}
