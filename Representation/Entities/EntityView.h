#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include <SFML/Graphics/Sprite.hpp>

#include "../../Logic/Entities/EntityModel.h"


class EntityView : public logic::Observer {
public:
    /**
     * Abstract EntityView class. Initiates sprite offset to 0.8, 0.8 as that
     * is centered on my 16x16 pixel representation.
     * @param model Reference model
     * @param frameDuration Length of a single frame
     */
    explicit EntityView(const std::shared_ptr<logic::EntityModel>& model, float frameDuration);

    /**
     * @return Whether Entity is marked for deletion.
     */
    [[nodiscard]] bool shouldDelete() const;

    /**
     * @brief Calculates the current frameIndex based on the elapsed time.
     * @param dt Stopwatch time.
     * @param frameLimit Maximum frame index.
     * @return Current frame index.
     */
    [[nodiscard]] size_t getFrameIndex(float dt, size_t frameLimit);


    /**
     * @brief Determines how the sprites should react when the Screen dimension
     * changes.
     */
    virtual void resized();

    /**
     * @brief Determines what needs to happen to sprites when they should be
     * rendered.
     */
    virtual void render();

protected:
    std::shared_ptr<logic::EntityModel> model;
    sf::Sprite sprite;

    bool markedForDeletion = false;

    // Animation relatded variables
    float frameDuration;
    float elapsedTime = 0;
    size_t frameIndex = 0;
};



#endif //ENTITYVIEW_H
