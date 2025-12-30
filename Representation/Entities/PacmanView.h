#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include <unordered_map>

#include "../../Logic/Entities/PacmanModel.h"
#include "EntityView.h"


class PacmanView final : public EntityView {
public:
    explicit PacmanView(const std::shared_ptr<logic::PacmanModel> &model);

    void update(logic::Events event) override;
    void resized() override;
    void render() override;

private:
    // I store the PacmanModel in the view insteawd of dynamic casting the
    // generic model used in the base EntityView class to use PacmanModel
    // specific functions.
    std::shared_ptr<logic::PacmanModel> pacman;

    bool moving = true;
    bool dying = false;

    std::unordered_map<int, std::vector<sf::IntRect>> animations{};
    int animationIndex;

    sf::Sprite directionSprite;
};



#endif //PACMANVIEW_H
