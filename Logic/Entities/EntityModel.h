#ifndef ENTITYMODEL_H
#define ENTITYMODEL_H

#include "../Observer.h"


namespace logic {
    enum Moves { UP, LEFT, RIGHT, DOWN };

    class World;

    class EntityModel : public Subject {
    public:
        /**
         * @brief Base class for entities.
         * @param normalizedX Normalized initial X coordinate
         * @param normalizedY Normalized initial Y coordinate
         */
        explicit EntityModel(float normalizedX, float normalizedY);
        ~EntityModel() override = default;


        /**
         * @return normalized X coordinate
         */
        [[nodiscard]] float getX() const;

        /**
         * @return normalized Y coordinate
         */
        [[nodiscard]] float getY() const;

    protected:
        float x;
        float y;
    };


    class CollectibleEntityModel : public EntityModel {
    public:
        /**
         * @brief Subclass of EntityModel to be used by collectible entities.
         * @param normalizedX Normalized initial X coordinate
         * @param normalizedY Normalized initial Y coordinate
         */
        explicit CollectibleEntityModel(float normalizedX, float normalizedY);


        /**
         * @brief Function that will be called when Pacman interacts with a
         * collectible entity. Must handle this interaction.
         * @return Event for the World to notify its observers of
         */
        [[nodiscard]] virtual Events collect() = 0;
    };


    constexpr float TARGET_EPSILON = 0.001f;

    class MovingEntityModel : public EntityModel {
    public:
        /**
         * @brief Subclass of EntityModel to be used for any moving entity.
         * @param normalizedX Normalized initial X coordinate
         * @param normalizedY Normalized initial Y coordinate
         * @param mapWidth Map width (in tiles)
         * @param mapHeight Map height (in tiles)
         * @param speed Default speed of entity
         */
        MovingEntityModel(float normalizedX, float normalizedY, float mapWidth, float mapHeight, float speed);


        /**
         * @brief Get the direction the entity is currently moving in.
         * @return Current direction
         */
        [[nodiscard]] Moves getDirection() const;

        /**
         * @return Current grid aligned X coordinate
         */
        [[nodiscard]] int getGridX() const;

        /**
         * @return Current grid aligned Y coordinate
         */
        [[nodiscard]] int getGridY() const;


        /**
         * @brief Called within the World update loop and should update the
         * position of the entity or handle moving the entity appropriately.
         * @param world World
         * @param dt Deltatime since last call
         */
        virtual void move(const World &world, float dt) = 0;

        /**
         * @brief Called when an entity should respawn, this means it died and
         * should be 'reset' to some extent.
         */
        virtual void respawn() = 0;

    protected:
        /**
         * @brief This function should be called when the MovingEntity has
         * reached its targetX and targetY values (within a certain Epsilon).
         * @param world World
         * @return Whether the entity continues down its current direction.
         */
        virtual bool gridTargetReached(const World& world) = 0;

        /**
         * @brief Normalizes the grid coordinates and stores these values in as
         * target coordinates. Moving entities strive towards normalized grid
         * coordinates.
         */
        void normalizeTarget();

        float mapWidth;
        float mapHeight;

        float spawnX;
        float spawnY;

        int gridY;
        int gridX;
        float targetX;
        float targetY;

        Moves direction = Moves::RIGHT;
        float speed;
    };
}



#endif //ENTITYMODEL_H
