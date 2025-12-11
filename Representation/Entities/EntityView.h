//
// Created by PPetre on 26/11/2025.
//

#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include <SFML/Graphics/Sprite.hpp>

#include "../../Logic/Entities/EntityModel.h"
#include "../../Logic/Observer.h"
#include "../Camera.h"


class EntityView : public logic::Observer {
public:
    explicit EntityView(const std::shared_ptr<logic::EntityModel>& model, const std::shared_ptr<Camera>& camera, float frameDuration);

    [[nodiscard]] size_t getFrameIndex(float dt, size_t max);

    virtual void render();

protected:
    std::shared_ptr<logic::EntityModel> model;
    std::shared_ptr<Camera> camera;
    sf::Sprite sprite;

    // Animation
    float frameDuration;
    float elapsedTime = 0;
    size_t frameIndex = 0;
};



#endif //ENTITYVIEW_H
