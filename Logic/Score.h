#ifndef PACMAN_SCORE_H
#define PACMAN_SCORE_H

#include <fstream>
#include <utility>
#include <vector>

#include "Observer.h"


namespace logic {

    constexpr int SCORE_DECAY = 10; // 10 points per second
    constexpr int GHOST_POINTS = 200;
    constexpr int LEVEL_CLEAR_POINTS = 500;
    constexpr int BASE_COIN_POINTS = 10;


    /**
     * Helper struct which links a username with a score. Also implements an
     * override for the less than operator which is used to sort Highscore
     * objects based on the score they hold.
     */
    struct ScoreEntry {
        std::string username;
        int score;

        /**
         * @brief Default constructor initiates an empty object.
         */
        ScoreEntry() : username(""), score(0) {}

        /**
         * @brief Constructs a new ScoreEntry object, populated with the
         * provided values.
         * @param username Username of person with score
         * @param score Score
         */
        ScoreEntry(std::string username, const int score) : username(std::move(username)), score(score) {}


        /**
         * @brief Accesses the score member variables and compares them.
         * @param other Other ScoreEntry object for comparison
         * @return Whether the score of this is smaller than other
         */
        bool operator<(const ScoreEntry& other) const {
            return score > other.score;
        }
    };


    class Score final : public Observer, public Subject {
    public:
        /**
         * @brief Creates new Score object, and loads entries from
         * highscores.txt file.
         */
        Score();

        /**
         * @brief Overrides destructor behaviour to call Score::write;
         */
        ~Score() override;


        /**
         * @brief Returns a reference to the vector holding all known
         * Highscore objects.
         * @return Reference to Highscores vector
         */
        [[nodiscard]] std::vector<std::unique_ptr<ScoreEntry>>& getHighscores();

        /**
         * @brief Returns the current score.
         *
         * The current score is updated by World events while the World is
         * active so the score will vary from time to time.
         *
         * @return Current score
         */
        [[nodiscard]] int getScore() const;

        /**
         * @brief Returns the last achieved score as a Highscore object.
         * @return Last score
         */
        [[nodiscard]] const ScoreEntry& getLastScore() const;


        /**
         * @brief Sets the user to whom the next ScoreEntry will be attributed.
         * @param username
         */
        void setUser(const std::string& username);

        /**
         * @brief Updates time since last coin collection and time accumulator,
         * te determine score decay.
         * @param dt Deltatime
         */
        void update(double dt);

        /**
         * @brief Creates a new score entry for the current user with the
         * current score.
         */
        void addScoreEntry();

        /**
         * @brief Writes the ScoreEntry objects to the highscores.txt file.
         */
        void write() const;

    private:

        /**
         * @brief Creates a highscores.txt file with no contents.
         */
        void createHighscoresFile() const;

        /**
         * @brief Updates the score based on specific world events.
         * @param event World events
         */
        void update(Events event) override;

        std::string filename = "highscores.txt";
        std::vector<std::unique_ptr<ScoreEntry>> highscores;
        std::string username;
        ScoreEntry lastScore{};

        // While the World is restarting scores should not be decaying.
        bool paused = false;
        int score;

        double timeLastCoin = 0;
        double accumulator = 0;

        // Since ghost eating points are exponential when done in a row, I keep
        // track of the current amount.
        int ghostPoints = 0;
    };
}

#endif //PACMAN_SCORE_H