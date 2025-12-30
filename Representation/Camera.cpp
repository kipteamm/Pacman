#include "Camera.h"
#include "Window.h"


Camera::Camera() {
    screenWidth = static_cast<float>(Window::getInstance().getWidth());
    // Subtracting 100 pixels from the screenheight to assure that the Game
    // text UI always fits on screen.
    screenHeight = static_cast<float>(Window::getInstance().getHeight()) - 100;

    mapWidth = 0;
    mapHeight = 0;
    tileWidth = 0;
    tileHeight = 0;
    offsetX = 0;
    offsetY = 0;
    viewWidth = 0;
    viewHeight = 0;
}


Camera& Camera::getInstance() {
    // The instance is created the first time this function is called.
    // It is destroyed automatically when the program exits.
    static Camera instance;
    return instance;
}


void Camera::setScaling(const float mapWidth, const float mapHeight) {
    // Calculate what the smallest dimension is (width or height) and take that
    // as the scaling factor. Assures that the map always fits entirely on
    // screen.
    const float scaleX = screenWidth / mapWidth;
    const float scaleY = screenHeight / mapHeight;
    const float scale = std::min(scaleX, scaleY);

    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;

    tileWidth = scale;
    tileHeight = scale;

    viewWidth = mapWidth * tileWidth;
    viewHeight = mapHeight * tileHeight;

    // Used for centering
    offsetX = (screenWidth - viewWidth) / 2.0f;
    offsetY = (screenHeight - viewHeight) / 2.0f;
}

void Camera::resized() {
    this->screenWidth = static_cast<float>(Window::getInstance().getWidth());
    // Subtracting 100 pixels from the screenheight to assure that the Game
    // text UI always fits on screen.
    this->screenHeight = static_cast<float>(Window::getInstance().getHeight() - 100);

    if (mapWidth == 0 || mapHeight == 0) return;
    // Rescale everything based on the (unchanged) map dimensions and changed
    // window dimensions.
    this->setScaling(mapWidth, mapHeight);
}


float Camera::xToPixel(const float normalizedX) const {
    return ((normalizedX + 1) / 2) * viewWidth + offsetX;
}

float Camera::yToPixel(const float normalizedY) const {
    return ((normalizedY + 1) / 2) * viewHeight + offsetY;
}

float Camera::getTileWidth() const {
    return tileWidth;
}

float Camera::getTileHeight() const {
    return tileHeight;
}


