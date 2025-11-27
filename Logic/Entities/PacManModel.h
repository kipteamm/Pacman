//
// Created by PPetre on 27/11/2025.
//

#ifndef PACMANMODEL_H
#define PACMANMODEL_H

#include "EntityModel.h"


namespace logic {

    class PacManModel final : public EntityModel {
    public:
        explicit PacManModel(float normalizedX, float normalizedY);

        void update(double dt) override;
    };
}



#endif //PACMANMODEL_H
