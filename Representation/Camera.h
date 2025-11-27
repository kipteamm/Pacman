//
// Created by PPetre on 27/11/2025.
//

#ifndef CAMERA_H
#define CAMERA_H


class Camera {
public:
    explicit Camera(int width, int height);

    double xToPixel(double normalizedX) const;
    double yToPixel(double normalizedY) const;

private:
    int screenWidth;
    int screenHeight;
};



#endif //CAMERA_H
