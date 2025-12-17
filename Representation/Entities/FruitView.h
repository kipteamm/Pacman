//
// Created by PPetre on 12/12/2025.
//

#ifndef FRUITVIEW_H
#define FRUITVIEW_H

#include "../../Logic/Entities/FruitModel.h"
#include "EntityView.h"


class FruitView final : public EntityView {
public:
    explicit FruitView(const std::shared_ptr<logic::FruitModel> &model);

    void update(logic::Events event) override;
};



#endif //FRUITVIEW_H
