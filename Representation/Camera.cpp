//
// Created by PPetre on 27/11/2025.
//

#include "Camera.h"


Camera::Camera(const int width, const int height) : screenWidth(width), screenHeight(height) {}


double Camera::xToPixel(const double normalizedX) const {
    return (normalizedX + 1) / 2 * screenWidth;
}

double Camera::yToPixel(const double normalizedY) const {
    return (normalizedY + 1) / 2 * screenHeight;
}

