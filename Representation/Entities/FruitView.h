#ifndef FRUITVIEW_H
#define FRUITVIEW_H

#include "../../Logic/Entities/FruitModel.h"
#include "EntityView.h"


class FruitView final : public EntityView {
public:
    /**
     * @brief FruitView renders fruit.
     * @param model Reference model
     */
    explicit FruitView(const std::shared_ptr<logic::FruitModel> &model);

    /**
     * @brief Marks this View for deletion when it's model is destroyed by the
     * World
     * @param event World events
     */
    void update(logic::Events event) override;
};



#endif //FRUITVIEW_H
