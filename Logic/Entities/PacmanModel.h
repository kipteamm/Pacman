#ifndef PACMANMODEL_H
#define PACMANMODEL_H

#include "EntityModel.h"


namespace logic {

    class PacmanModel final : public MovingEntityModel {
    public:
        PacmanModel(float normalizedX, float normalizedY, float mapWidth, float mapHeight);

        [[nodiscard]] Moves getNextDirection() const;
        [[nodiscard]] bool isMoving() const;

        void setNextDirection(const Moves& move);
        void move(const World& world, float dt) override;
        void respawn() override;

    private:
        Moves nextDirection;
        bool moving;

        [[nodiscard]] bool canMoveInDirection(const World& world, Moves dir) const;
    };

} // namespace logic

#endif // PACMANMODEL_H