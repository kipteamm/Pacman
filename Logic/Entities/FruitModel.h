//
// Created by PPetre on 12/12/2025.
//

#ifndef FRUITMODEL_H
#define FRUITMODEL_H
#include "EntityModel.h"


namespace logic {

    class FruitModel final : public CollectibleEntityModel {
    public:
        explicit FruitModel(float normalizedX, float normalizedY, unsigned int score);

        [[nodiscard]] Events collect() override;
    private:
        unsigned int score;
    };
}




#endif //FRUITMODEL_H
