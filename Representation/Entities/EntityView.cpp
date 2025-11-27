//
// Created by PPetre on 26/11/2025.
//

#include "EntityView.h"


EntityView::EntityView(const std::shared_ptr<logic::EntityModel> &model, const std::shared_ptr<Camera>& camera) : model(model), camera(camera) {}
