#ifndef PACMAN_COINVIEW_H
#define PACMAN_COINVIEW_H

#include "../../Logic/Entities/CoinModel.h"
#include "EntityView.h"


class CoinView final : public EntityView {
public:
    /**
     * @brief CoinView renders fruit.
     * @param model Reference model
     */
    explicit CoinView(const std::shared_ptr<logic::CoinModel> &model);

private:
    /**
     * @brief Marks this View for deletion when it's model is destroyed by the
     * World
     * @param event World events
     */
    void update(logic::Events event) override;
};


#endif //PACMAN_COINVIEW_H