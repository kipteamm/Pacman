//
// Created by PPetre on 26/11/2025.
//

#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include "../Observer.h"


namespace logic {
    enum Moves { NONE, UP, LEFT, RIGHT, DOWN };

    class EntityModel : public Subject {
    public:
        explicit EntityModel(float normalizedX, float normalizedY);
        ~EntityModel() override = default;

        virtual void update(double dt) = 0;

        [[nodiscard]] bool checkCollision(float otherX, float otherY, float width, float height) const;
        [[nodiscard]] float getX() const;
        [[nodiscard]] float getY() const;

    protected:
        float x;
        float y;
    };

    class World;

    class MovingEntityModel : public EntityModel {
    public:
        MovingEntityModel(float x, float y, float speed);

        virtual void move(const World &world, float dt) = 0;

        [[nodiscard]] Moves getDirection() const;
        [[nodiscard]] float getSpeed() const;

    protected:
        float speed;

        Moves direction = NONE;
    };
}



#endif //ENTITYMODEL_H
