#ifndef PACMAN_WALLVIEW_H
#define PACMAN_WALLVIEW_H

#include "../../Logic/Entities/WallModel.h"
#include "EntityView.h"


class WallView final : public EntityView {
public:
    /**
     * @brief WallView renders a specific wall piece.
     * @param model Reference Model
     * @param type Char to determine the sprite
     */
    explicit WallView(const std::shared_ptr<logic::WallModel> &model, char type);

    // Not implemented.
    void update(logic::Events event) override {};
};


#endif //PACMAN_WALLVIEW_H