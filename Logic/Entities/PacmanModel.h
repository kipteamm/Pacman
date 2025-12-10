#ifndef PACMANMODEL_H
#define PACMANMODEL_H

#include "EntityModel.h"


namespace logic {

    class PacmanModel final : public MovingEntityModel {
    public:
        PacmanModel(float normalizedX, float normalizedY, float mapWidth, float mapHeight, float speed);

        [[nodiscard]] Moves getNextDirection() const;
        [[nodiscard]] bool isMoving() const;

        void setNextDirection(const Moves& move);
        void move(const World& world, float dt) override;
        void update(double dt) override;


    private:
        Moves nextDirection;
        bool moving;

        void updateTarget();

        [[nodiscard]] bool canMoveInDirection(const World& world, Moves dir) const;
    };

} // namespace logic

#endif // PACMANMODEL_H