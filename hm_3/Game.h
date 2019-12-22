#pragma once
#include <fstream>

class Game {
public:
    Game(const Options& option) :
        dif(option.getDif()),
        timerOn(option.getTimerOn()) {}

    bool loadSaveFromFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file)
            return false;
        
        return true;
    }

    void startGame() {
        init();
    }
private:
    void init() {
        // readmap();
        // readconfig();
    }

    const int dif;
    const bool timerOn;
    std::vector<std::vector<char>> map
};