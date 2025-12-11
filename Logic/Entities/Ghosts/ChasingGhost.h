//
// Created by PPetre on 11/12/2025.
//

#ifndef CHASINGGHOST_H
#define CHASINGGHOST_H
#include "GhostModel.h"


namespace logic {

    class ChasingGhost final : public GhostModel {
    public:
        explicit ChasingGhost(float normalizedX, float normalizedY, float mapWidth, float mapHeight, float speed, double cooldown);

    private:
        Moves decideNextMove(const World &world, const PacmanModel &pacman) override;
    };
}



#endif //CHASINGGHOST_H
