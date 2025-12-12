//
// Created by toroe on 28/11/2025.
//

#ifndef PACMAN_COINVIEW_H
#define PACMAN_COINVIEW_H

#include "../../Logic/Entities/CoinModel.h"
#include "EntityView.h"


class CoinView final : public EntityView {
public:
    explicit CoinView(const std::shared_ptr<logic::CoinModel> &model, const std::shared_ptr<Camera> &camera);

    void update(logic::Events event) override;
};


#endif //PACMAN_COINVIEW_H