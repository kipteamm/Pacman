//
// Created by toroe on 25/11/2025.
//

#ifndef PACMAN_STATE_H
#define PACMAN_STATE_H

#include <memory>

#include "../Logic/Score.h"

#include <SFML/Graphics.hpp>


class State {
public:
    State() = default;
    virtual ~State() = default;

    virtual void update() = 0;
    virtual void handleInput(const sf::Event::KeyEvent &keyPressed) = 0;
    virtual void render() = 0;
};


class MenuState final : public State {
public:
    explicit MenuState(const std::shared_ptr<logic::Score>& scoreSystem);

    void update() override {};
    void handleInput(const sf::Event::KeyEvent &keyPressed) override {};
    void render() override;

private:
    std::shared_ptr<logic::Score> scoreSystem;

    sf::Texture pacmanLogoTexture;
    sf::Sprite pacmanLogo;
};


#endif //PACMAN_STATE_H