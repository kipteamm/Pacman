#ifndef CAMERA_H
#define CAMERA_H


class Camera {
public:
    /**
     * Singletons should not be cloneable or assignable.
     */
    Camera(Camera &other) = delete;
    void operator=(const Camera &) = delete;

    /**
     * @brief Returns an instance of the Camera class
     *
     * @return Camera instance
     */
    [[nodiscard]] static Camera& getInstance();


    /**
     * @brief Update the Camera scaling factors based on the current world.
     *
     * This must be done to assure that the whole world will always fit on
     * screen. Regardless of map or window size.
     *
     * @param mapWidth The loaded world map width in tiles
     * @param mapHeight The loaded world map height in tiles
     */
    void setScaling(float mapWidth, float mapHeight);

    /**
     * @brief Update the Camera scaling factors based on the current window
     * size.
     *
     * When the window is resized it is important that this is properly
     * reflected by the Camera. Will call setScaling afterward.
     */
    void resize();


    /**
     *
     * @param normalizedX Normalized world X coordinate.
     * @return X coordinate scaled appropriately for the current window width.
     */
    [[nodiscard]] float xToPixel(float normalizedX) const;

    /**
     *
     * @param normalizedY Normalized world Y coordinate.
     * @return Y coordinate scaled appropriately for the current window height.
     */
    [[nodiscard]] float yToPixel(float normalizedY) const;


    /**
     * @brief Returns the width of a tile according to the current scaling
     * factors
     *
     * @return Width of a tile
     */
    [[nodiscard]] float getTileWidth() const;

    /**
     * @brief Returns the height of a tile according to the current scaling
     * factors
     *
     * @return Height of a tile
     */
    [[nodiscard]] float getTileHeight() const;

private:
    Camera();

    float screenWidth;
    float screenHeight;

    // Mapped to the screen size
    float tileWidth;
    float tileHeight;

    // Final dimensions of the world when fit to the screen size
    float viewWidth;
    float viewHeight;

    float offsetX;
    float offsetY;
};



#endif //CAMERA_H
