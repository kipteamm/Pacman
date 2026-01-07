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

        [[nodiscard]] float getX() const;
        [[nodiscard]] float getY() const;

    protected:
        float x;
        float y;
    };


    class CollectibleEntityModel : public EntityModel {
    public:
        explicit CollectibleEntityModel(float normalizedX, float normalizedY);

        [[nodiscard]] virtual Events collect() = 0;
    };


    constexpr float TARGET_EPSILON = 0.001f;

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

        void updateGridTarget();

        /**
         * @brief This function should be called when the MovingEntity has
         * reached its targetX and targetY values (within a certain Epsilon).
         *
         * It keeps the grid coordinates up to date and possibly teleports the
         * Ghost when it is
         *
         * @param world World
         */
        void gridTargetReached(const World& world);
    };
}



#endif //ENTITYMODEL_H
