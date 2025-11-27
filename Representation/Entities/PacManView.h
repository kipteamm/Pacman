//
// Created by PPetre on 27/11/2025.
//

#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include "../../Logic/Entities/PacManModel.h"
#include "EntityView.h"


class PacManView : public EntityView {
public:
    explicit PacManView(const std::shared_ptr<logic::PacManModel> &model);

    void draw() override {};
    void update() override {};
};



#endif //PACMANVIEW_H
