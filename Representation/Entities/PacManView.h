//
// Created by PPetre on 27/11/2025.
//

#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include <SFML/Graphics/Sprite.hpp>

#include "../../Logic/Entities/PacManModel.h"
#include "EntityView.h"


class PacManView final : public EntityView {
public:
    explicit PacManView(const std::shared_ptr<logic::PacManModel> &model, const std::shared_ptr<Camera> &camera);

    void update() override {};
};



#endif //PACMANVIEW_H
