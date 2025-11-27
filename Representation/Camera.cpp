//
// Created by PPetre on 27/11/2025.
//

#include "Camera.h"

#include "Window.h"


Camera::Camera() {
    screenWidth = static_cast<float>(Window::getInstance().getWidth());
    screenHeight = static_cast<float>(Window::getInstance().getHeight());
}


float Camera::xToPixel(const float normalizedX) const {
    return (normalizedX + 1) / 2 * screenWidth;
}

float Camera::yToPixel(const float normalizedY) const {
    return (normalizedY + 1) / 2 * screenHeight;
}

