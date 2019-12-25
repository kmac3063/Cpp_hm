#pragma once

#include "Map/Map.h"

namespace Game {
class Game {
public:
    ~Game();

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

    std::vector<GameObject::GameObject*> objects;
    Map::Map* map;

    GameObject::Hero* hero;

    int level = 0;
};
}  // namespace Game