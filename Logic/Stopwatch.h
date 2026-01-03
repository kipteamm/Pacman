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

        /**
         * @brief Returns an instance of the Stopwatch class.
         * @return Stopwatch instance
         */
        [[nodiscard]] static Stopwatch& getInstance();


        /**
         * @brief Returns the deltatime, updated by Stopwatch::tick.
         * @return Deltatime
         */
        [[nodiscard]] double getDeltaTime() const;

        /**
         * @brief Updates deltatime to hold the time difference between now and
         * the last tick.
         */
        void tick();

        /**
         * @brief Resets the Stopwatch.
         */
        void reset();

    private:
        Stopwatch();

        std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
        double deltaTime = 0.0;
    };
}


#endif //STOPWATCH_H
