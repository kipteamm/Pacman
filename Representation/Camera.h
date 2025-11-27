//
// Created by PPetre on 27/11/2025.
//

#ifndef CAMERA_H
#define CAMERA_H


class Camera {
public:
    explicit Camera();

    [[nodiscard]] float xToPixel(float normalizedX) const;
    [[nodiscard]] float yToPixel(float normalizedY) const;

private:
    float screenWidth;
    float screenHeight;
};



#endif //CAMERA_H
