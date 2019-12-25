#pragma once

#include "Map/Map.h"

namespace Game {
class Game {
public:
    ~Game();

    void loadSaveFile();

    void startGame();

private:
    void drawAll();

    void drawInterface(const int& y, const int& x);

    void init();

    void readConfig();

    void readMap();

    void updateObjects();

    void collideObjects();

    time_t startTime;

    std::vector<GameObject::GameObject*> objects;
    Map::Map* map;

    GameObject::Hero* hero;
};
}  // namespace Game