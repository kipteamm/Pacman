//
// Created by PPetre on 24/11/2025.
//

#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <chrono>


namespace logic {
    class Stopwatch {
    public:
        /**
         * Singletons should not be cloneable or assignable.
         */
        Stopwatch(Stopwatch &other) = delete;
        void operator=(const Stopwatch &) = delete;

        [[nodiscard]] static Stopwatch& getInstance();
        [[nodiscard]] double getDeltaTime() const;

        void tick();
        void reset();

    private:
        Stopwatch();

        std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
        double deltaTime = 0.0;
    };
}


#endif //STOPWATCH_H
