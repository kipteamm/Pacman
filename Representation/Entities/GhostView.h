//
// Created by toroe on 09/12/2025.
//

#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H

#include "../../Logic/Entities/GhostModel.h"
#include "EntityView.h"


class GhostView final : public EntityView {
public:
    explicit GhostView(const std::shared_ptr<logic::GhostModel> &model, const std::shared_ptr<Camera> &camera, char type);

    void update() override {};
    void render() override;

private:
    int spriteY;
};


#endif //PACMAN_GHOSTVIEW_H