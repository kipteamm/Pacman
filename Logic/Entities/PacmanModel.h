//
// Created by PPetre on 27/11/2025.
//

#ifndef PACMANMODEL_H
#define PACMANMODEL_H

#include "EntityModel.h"


namespace logic {

    class PacmanModel final : public MovingEntityModel {
    public:
        explicit PacmanModel(float normalizedX, float normalizedY, float speed);

        [[nodiscard]] Moves getNextDirection() const;

        void setNextDirection(const Moves& move);

        void move(bool colliding, float x, float y) override;
        void update(double dt) override;

    private:
        Moves nextDirection;
    };
}



#endif //PACMANMODEL_H
