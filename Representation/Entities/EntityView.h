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
    explicit EntityView(const std::shared_ptr<logic::EntityModel>& model, const std::shared_ptr<Camera>& camera);

    void render();

protected:
    std::shared_ptr<logic::EntityModel> model;
    std::shared_ptr<Camera> camera;
    sf::Sprite sprite;
};



#endif //ENTITYVIEW_H
