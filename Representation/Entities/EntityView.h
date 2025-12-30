//
// Created by PPetre on 26/11/2025.
//

#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include <SFML/Graphics/Sprite.hpp>

#include "../../Logic/Entities/EntityModel.h"


class EntityView : public logic::Observer {
public:
    explicit EntityView(const std::shared_ptr<logic::EntityModel>& model, float frameDuration);

    [[nodiscard]] bool shouldDelete() const;
    [[nodiscard]] size_t getFrameIndex(float dt, size_t max);

    virtual void resized();
    virtual void render();

protected:
    std::shared_ptr<logic::EntityModel> model;
    sf::Sprite sprite;

    bool markedForDeletion = false;

    // Animation
    float frameDuration;
    float elapsedTime = 0;
    size_t frameIndex = 0;
};



#endif //ENTITYVIEW_H
