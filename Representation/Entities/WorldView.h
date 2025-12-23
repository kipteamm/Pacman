//
// Created by toroe on 19/12/2025.
//

#ifndef PACMAN_WORLDVIEW_H
#define PACMAN_WORLDVIEW_H

#include <SFML/Graphics.hpp>

#include "../../Logic/Observer.h"
#include "../../Logic/Score.h"
#include "../../Logic/World.h"


class WorldView final : public logic::Observer {
public:
    explicit WorldView(const std::shared_ptr<logic::World>& world, const std::shared_ptr<logic::Score>& scoreSystem);

    void update(logic::Events event) override;
    void render() const;

private:
    std::shared_ptr<logic::World> world;
    std::shared_ptr<logic::Score> scoreSystem;

    std::vector<std::pair<double, sf::Sprite>> scores;

    sf::Sprite live1;
    sf::Sprite live2;
    sf::Sprite live3;

    sf::Text scoreText;
};


#endif //PACMAN_WORLDVIEW_H