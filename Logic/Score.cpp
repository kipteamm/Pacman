#include "Score.h"

#include <algorithm>


using namespace logic;



Score::Score() {
    // Try to open the file in read and write mode
    // If the fil does not exist, create it, the function
    // will try to reopen the file in read and write after creation
    std::fstream fileStream(filename);
    if (!fileStream.is_open()) fileStream = createHighscoresFile();

    fileStream.seekg(0);

    std::string line;
    while (std::getline(fileStream, line)) {
        highscores.push_back(std::stoi(line));
    }

    fileStream.close();
}

Score::~Score() {
    write();
}


std::vector<int> Score::getHighscores() {
    return highscores;
}


void Score::addScore(const int score) {
    highscores.push_back(score);

    std::ranges::sort(highscores, std::greater<>());
}

void Score::write() const {
    std::ofstream out(filename, std::ios::trunc);
    out.seekp(0);

    out << highscores[0];
    for (int i = 1; i < highscores.size(); i++) {
        out << "\n" << highscores[i];
    }

    out.close();
}


std::fstream Score::createHighscoresFile() const {
    std::fstream fileStream(filename, std::ios::out);
    fileStream.close();

    // After creation, try to reopen it in read & try mode
    fileStream.open(filename, std::ios::in | std::ios::out);

    if (!fileStream.is_open()) throw std::runtime_error("Could not create highscores file.");
    return fileStream;
}


void Score::update(const int& subject) {
    return;
}

