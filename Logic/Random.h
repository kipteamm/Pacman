#ifndef RANDOM_H
#define RANDOM_H

#include <random>


namespace logic {

    /**
     * Singleton wrapper for the Mersenne Twister random number engine.
     */
    class Random {
    public:
        /**
         * Singletons should not be cloneable or assignable.
         */
        Random(Random &other) = delete;
        void operator=(const Random &) = delete;


        /**
         * @brief Returns an instance of the Random class
         * @return Random instance
         */
        [[nodiscard]] static Random& getInstance();

        /**
         * @brief Function that returns a random float value between 0 and 1.
         * @return Random float between 0 and 1
         */
        [[nodiscard]] float getFloat();

        /**
         * @brief Helper function that returns a random value between the given
         * min and max. Including the max.
         * @param min
         * @param max
         * @return
         */
        [[nodiscard]] int getInt(int min, int max);

    private:
        Random();

        std::mt19937 generator;
    };
}




#endif //RANDOM_H
