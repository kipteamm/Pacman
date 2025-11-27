//
// Created by PPetre on 26/11/2025.
//

#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include "../Observer.h"


namespace logic {

    class EntityModel : public Subject {
    public:
        explicit EntityModel(float normalizedX, float normalizedY);
        ~EntityModel() override = default;

        virtual void update(double dt) = 0;

        [[nodiscard]] float getX() const;
        [[nodiscard]] float getY() const;

    protected:
        float x;
        float y;
    };
}



#endif //ENTITYMODEL_H
