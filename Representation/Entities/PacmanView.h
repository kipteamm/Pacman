//
// Created by PPetre on 27/11/2025.
//

#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include <SFML/Graphics/Sprite.hpp>
#include <unordered_map>

#include "../../Logic/Entities/PacmanModel.h"
#include "EntityView.h"


class PacmanView final : public EntityView {
public:
    explicit PacmanView(const std::shared_ptr<logic::PacmanModel> &model, const std::shared_ptr<Camera> &camera);

    void update(logic::Events event) override;
    void render() override;

private:
    // As the PacmanModel is a shared pointer we store it in the view as well
    // to use PacmanModel specific functions without needing to dynamic cast
    std::shared_ptr<logic::PacmanModel> pacman;
    bool moving = true;

    std::unordered_map<logic::Moves, std::vector<sf::IntRect>> animations{};
    std::vector<sf::IntRect>* animation;

    sf::Sprite directionSprite;
};



#endif //PACMANVIEW_H
