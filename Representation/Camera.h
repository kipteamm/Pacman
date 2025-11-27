//
// Created by PPetre on 27/11/2025.
//

#ifndef CAMERA_H
#define CAMERA_H


class Camera {
public:
    explicit Camera();

    void setScaling(float mapWidth, float mapHeight);

    [[nodiscard]] float xToPixel(float normalizedX) const;
    [[nodiscard]] float yToPixel(float normalizedY) const;

    [[nodiscard]] float getTileWidth() const;
    [[nodiscard]] float getTileHeight() const;

private:
    float screenWidth;
    float screenHeight;

    float tileWidth;
    float tileHeight;

    float viewWidth;
    float viewHeight;

    float offsetX;
    float offsetY;
};



#endif //CAMERA_H
