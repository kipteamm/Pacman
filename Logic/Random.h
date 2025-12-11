//
// Created by PPetre on 11/12/2025.
//

#ifndef RANDOM_H
#define RANDOM_H
#include <random>


namespace logic {

    class Random {
    public:
        /**
         * Singletons should not be cloneable or assignable.
         */
        Random(Random &other) = delete;
        void operator=(const Random &) = delete;

        [[nodiscard]] static Random& getInstance();
        [[nodiscard]] float getFloat();
        [[nodiscard]] int getInt(int min, int max);

    private:
        Random();

        std::mt19937 generator;
    };
}




#endif //RANDOM_H
