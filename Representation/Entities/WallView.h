//
// Created by toroe on 27/11/2025.
//

#ifndef PACMAN_WALLVIEW_H
#define PACMAN_WALLVIEW_H

#include "../../Logic/Entities/WallModel.h"
#include "EntityView.h"


class WallView final : public EntityView {
public:
    explicit WallView(const std::shared_ptr<logic::WallModel> &model, const std::shared_ptr<Camera> &camera, char type);

    void update(logic::Events event) override {};
};


#endif //PACMAN_WALLVIEW_H