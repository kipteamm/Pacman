//
// Created by PPetre on 26/11/2025.
//

#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include "../Observer.h"


namespace logic {
    enum Moves { UP, LEFT, RIGHT, DOWN };

    class World;

    class EntityModel : public Subject {
    public:
        explicit EntityModel(float normalizedX, float normalizedY);
        ~EntityModel() override = default;

        virtual void update(const World& world, double dt) = 0;

        [[nodiscard]] bool checkCollision(float otherX, float otherY, float width, float height) const;
        [[nodiscard]] float getX() const;
        [[nodiscard]] float getY() const;

    protected:
        float x;
        float y;
    };

    class MovingEntityModel : public EntityModel {
    public:
        MovingEntityModel(float x, float y, float mapWidth, float mapHeight, float speed);

        virtual void move(const World &world, float dt) = 0;
        virtual void respawn() = 0;

        [[nodiscard]] Moves getDirection() const;
        [[nodiscard]] float getSpeed() const;

        [[nodiscard]] int getGridX() const { return gridX; }
        [[nodiscard]] int getGridY() const { return gridY; }

    protected:
        float mapWidth;
        float mapHeight;
        float spawnX;
        float spawnY;

        float targetX;
        float targetY;

        int gridX;
        int gridY;

        float speed;

        Moves direction = Moves::RIGHT;

        void updateTarget();
    };
}



#endif //ENTITYMODEL_H
