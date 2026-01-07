//
// Created by PPetre on 11/12/2025.
//

#ifndef RANDOMGHOST_H
#define RANDOMGHOST_H

#include "GhostModel.h"


namespace logic {

    class RandomGhost final : public GhostModel {
    public:
        explicit RandomGhost(float normalizedX, float normalizedY, float mapWidth, float mapHeight, double cooldown);

    private:
        Moves decideNextMove(const World &world) override;
    };
}


#endif //RANDOMGHOST_H
