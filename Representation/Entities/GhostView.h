//
// Created by toroe on 09/12/2025.
//

#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H

#include <unordered_map>

#include "../../Logic/Entities/Ghosts/GhostModel.h"
#include "EntityView.h"


class GhostView final : public EntityView {
public:
    explicit GhostView(const std::shared_ptr<logic::GhostModel> &model, const std::shared_ptr<Camera> &camera, int spriteY);

    void update(logic::Events event) override {};
    void render() override;

private:
    std::shared_ptr<logic::GhostModel> ghost;

    std::unordered_map<logic::Moves, std::vector<sf::IntRect>> animations{};
    std::vector<sf::IntRect>* animation;
};


#endif //PACMAN_GHOSTVIEW_H