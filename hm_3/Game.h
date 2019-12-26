#pragma once

#include <memory>

#include "Map/Map.h"

namespace Game {
class Game {
public:
    void loadSaveFile();

    void startNewGame();

    void startGame();

private:
    void drawAll();

    void drawInterface(const int& y, const int& x);

    void init();

    void readConfig();

    void updateObjects();

    virtual void collideObjects();

    void nextLevel();

    void saveProgress(const int& level);

    time_t startTime;

    std::vector<std::shared_ptr<GameObject::GameObject>> objects;
    std::shared_ptr<Map::Map> map;

    std::shared_ptr<GameObject::Hero> hero;

    int level = 0;
};
}  // namespace Game