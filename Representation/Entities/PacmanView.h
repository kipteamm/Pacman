//
// Created by PPetre on 27/11/2025.
//

#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include <SFML/Graphics/Sprite.hpp>

#include "../../Logic/Entities/PacmanModel.h"
#include "EntityView.h"


class PacmanView final : public EntityView {
public:
    explicit PacmanView(const std::shared_ptr<logic::PacmanModel> &model, const std::shared_ptr<Camera> &camera);

    void update() override {};
    void render() override;

private:
    // As the PacmanModel is a shared pointer we store it in the view as well
    // to use PacmanModel specific functions without needing to dynamic cast
    std::shared_ptr<logic::PacmanModel> pacman;

    sf::Sprite directionSprite;
};



#endif //PACMANVIEW_H
