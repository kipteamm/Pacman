#include "../../Logic/Stopwatch.h"
#include "../AssetManager.h"
#include "../Camera.h"
#include "../Window.h"
#include "WorldView.h"

#include <iostream>


ScorePopup::ScorePopup() : elapsedTime(0), active(false) {};


void ScorePopup::setScore(const int score) {
    switch (score) {
        case 100:
            sprite.setTextureRect(sf::IntRect(128, 80, 16, 16)); break;

        case 200:
            sprite.setTextureRect(sf::IntRect(128, 64, 16, 16)); break;

        case 300:
            sprite.setTextureRect(sf::IntRect(144, 80, 16, 16)); break;

        case 400:
            sprite.setTextureRect(sf::IntRect(144, 64, 16, 16)); break;

        case 500:
            sprite.setTextureRect(sf::IntRect(160, 80, 16, 16)); break;

        case 800:
            sprite.setTextureRect(sf::IntRect(160, 64, 16, 16)); break;

        case 700:
            sprite.setTextureRect(sf::IntRect(176, 80, 16, 16)); break;

        case 1600:
            sprite.setTextureRect(sf::IntRect(176, 64, 16, 16)); break;

        case 1000:
            sprite.setTextureRect(sf::IntRect(192, 32, 20, 16)); break;

        case 2000:
            sprite.setTextureRect(sf::IntRect(192, 48, 20, 16)); break;

        case 3000:
            sprite.setTextureRect(sf::IntRect(192, 64, 20, 16)); break;

        case 5000:
            sprite.setTextureRect(sf::IntRect(192, 80, 20, 16)); break;

        default: throw std::runtime_error("No score sprite known for '" + std::to_string(score) + "'");
    }
}


WorldView::WorldView(const std::shared_ptr<logic::World>& world, const std::shared_ptr<logic::Score>& scoreSystem) : world(world), scoreSystem(scoreSystem) {
    live1.setTexture(AssetManager::getInstance().getSpriteSheet());
    live2.setTexture(AssetManager::getInstance().getSpriteSheet());
    live3.setTexture(AssetManager::getInstance().getSpriteSheet());

    live1.setTextureRect({16, 0, 16, 16});
    live2.setTextureRect({16, 0, 16, 16});
    live3.setTextureRect({16, 0, 16, 16});

    for (int i = 0; i < 6; i++) {
        ScorePopup score = ScorePopup();
        score.sprite.setTexture(AssetManager::getInstance().getSpriteSheet());
        score.sprite.setOrigin(8.0f, 8.0f);

        scores.push_back(score);
    }

    this->resized();
}


void WorldView::update(const logic::Events event) {
    int score = 0;

    switch (event) {
        case logic::Events::SCORE_UPDATE:
            scoreText.setString(std::to_string(scoreSystem->getScore()));
            return;

        case logic::Events::GHOST_EATEN:
            score = scoreSystem->getGhostPoints() / 2; break;

        case logic::Events::FRUIT_EATEN:
            score = logic::Difficulty::getInstance().getDifficulty()->fruitPoints; break;

            default: return;
    }

    ScorePopup* scorePopup = nullptr;
    for (auto& _score : scores) {
        if (_score.active) continue;
        scorePopup = &_score;
        break;
    }

    if (scorePopup == nullptr) return;
    scorePopup->elapsedTime = 0;
    scorePopup->setScore(score);
    scorePopup->active = true;

    const auto [x, y] = world->getCollissionCoordinates();
    scorePopup->sprite.setPosition(
        Camera::getInstance().xToPixel(x),
        Camera::getInstance().yToPixel(y)
    );
}


void WorldView::resized() {
    const float scaleX = Camera::getInstance().getTileWidth() / 16.0f;
    const float scaleY = Camera::getInstance().getTileHeight() / 16.0f;

    live1.setScale(scaleX, scaleY);
    live2.setScale(scaleX, scaleY);
    live3.setScale(scaleX, scaleY);

    for (auto& score : scores) {
        score.sprite.setScale(scaleX, scaleY);
    }

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


void WorldView::render() {
    const unsigned int lives = world->getLives();
    if (lives > 0) Window::getInstance().draw(live1);
    if (lives > 1) Window::getInstance().draw(live2);
    if (lives > 2) Window::getInstance().draw(live3);

    const double dt = logic::Stopwatch::getInstance().getDeltaTime();

    for (auto& score : scores) {
        if (!score.active) continue;
        Window::getInstance().draw(score.sprite);

        score.elapsedTime += dt;
        if (score.elapsedTime > 1.4) score.active = false;
    }

    Window::getInstance().draw(scoreText);
}
