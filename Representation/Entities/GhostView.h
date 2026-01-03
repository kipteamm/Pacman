#ifndef PACMAN_GHOSTVIEW_H
#define PACMAN_GHOSTVIEW_H

#include <unordered_map>

#include "../../Logic/Entities/Ghosts/GhostModel.h"
#include "EntityView.h"


class GhostView final : public EntityView {
public:
    /**
     * @brief GhostView renders & animates Ghosts.
     * @param model Reference model
     * @param spriteY Used to differentiate between Ghost sprites (Blinky, Pinky, Inky, Clyde)
     */
    explicit GhostView(const std::shared_ptr<logic::GhostModel> &model, int spriteY);

    /**
     * @brief Renders the Ghost sprite.
     */
    void render() override;

private:
    /**
     * @brief Handles World events and animates or changes the view accordingly.
     * @param event World Events
     */
    void update(logic::Events event) override;

    std::shared_ptr<logic::GhostModel> ghost;

    std::unordered_map<int, std::vector<sf::IntRect>> animations{};
    int animationIndex;

    bool frightened = false;

    /// Ghosts have 2 sets of sprites that are direction based.
    ///     1. Normal moving about consisting of 4 directions with 2 frames
    ///        each, offset 0
    ///     2. A killed Ghost turns into eyes consisting of 4 directions with 2
    ///        frames each, offset 4
    /// By using offsets, I can do @code ghost->getDirection() +
    /// animationOffset @endcode for directions to work eitherway. The other
    /// possible sprites are Frightened and Flashing (flashing is a Ghost
    /// turning normal after being frightened). Both of these are not direction
    /// dependant so the animationIndex is set directly.
    int animationOffset = 0;
};


#endif //PACMAN_GHOSTVIEW_H