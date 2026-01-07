//
// Created by PPetre on 11/12/2025.
//

#ifndef AMBUSHGHOST_H
#define AMBUSHGHOST_H
#include "GhostModel.h"


namespace logic {

    class AmbushGhost final : public GhostModel {
        public:
            explicit AmbushGhost(float normalizedX, float normalizedY, float mapWidth, float mapHeight, double cooldown);

        private:
            Moves decideNextMove(const World &world) override;
    };
}


#endif //AMBUSHGHOST_H
