//
// Created by PPetre on 26/11/2025.
//

#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include "../../Logic/Entities/EntityModel.h"
#include "../../Logic/Observer.h"


class EntityView : public logic::Observer {
public:
    explicit EntityView(const std::shared_ptr<logic::EntityModel>& model);

    virtual void draw() = 0;

protected:
    std::shared_ptr<logic::EntityModel> model;
};



#endif //ENTITYVIEW_H
