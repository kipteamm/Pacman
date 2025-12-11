//
// Created by PPetre on 27/11/2025.
//

#include "Camera.h"

#include "Window.h"


Camera::Camera() {
    screenWidth = static_cast<float>(Window::getInstance().getWidth());
    screenHeight = static_cast<float>(Window::getInstance().getHeight()) - 100;

    tileWidth = 0;
    tileHeight = 0;
    offsetX = 0;
    offsetY = 0;
    viewWidth = 0;
    viewHeight = 0;
}


void Camera::setScaling(const float mapWidth, const float mapHeight) {
    const float scaleX = screenWidth / mapWidth;
    const float scaleY = screenHeight / mapHeight;
    const float scale = std::min(scaleX, scaleY);

    tileWidth = scale;
    tileHeight = scale;

    viewWidth = mapWidth * tileWidth;
    viewHeight = mapHeight * tileHeight;

    offsetX = (screenWidth - viewWidth) / 2.0f;
    offsetY = (screenHeight - viewHeight) / 2.0f;
}

void Camera::resize() {
    this->screenWidth = Window::getInstance().getWidth();
    this->screenHeight = Window::getInstance().getHeight() - 100;

    this->setScaling(this->viewWidth / tileWidth, this->viewHeight / tileHeight);
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


