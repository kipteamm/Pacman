//
// Created by PPetre on 26/11/2025.
//

#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include "../Observer.h"


namespace logic {

    class EntityModel : public Subject {
    public:
        explicit EntityModel(double x, double y);
        ~EntityModel() override = default;

        virtual void update(double dt);
    };
}



#endif //ENTITYMODEL_H
