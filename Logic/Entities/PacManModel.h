//
// Created by PPetre on 27/11/2025.
//

#ifndef PACMANMODEL_H
#define PACMANMODEL_H

#include "EntityModel.h"


namespace logic {

    class PacManModel final : public MovingEntityModel {
    public:
        explicit PacManModel(float normalizedX, float normalizedY, float speed);

        [[nodiscard]] Moves getNextDirection() const;

        void setNextDirection(const Moves& move);

        void move(bool colliding, float x, float y) override;
        void update(double dt) override;

    private:
        Moves nextDirection = RIGHT;
    };
}



#endif //PACMANMODEL_H
