#pragma once

#include <set>
#include <vector>

#include "../GameObject/GameObject.h"

namespace Map {
class Map {
 public:
    void readMapFromFile(std::vector<GameObject::GameObject*>& objects);
    
    int getWidth();

    int getHeight();

    void drawMap();

    void drawObjects(const std::vector<GameObject::GameObject*>& objects);

    std::pair<int, int> getYXForDrawing();

 private:
    int width;
    int height;

    std::set<std::pair<int, int>> filledCells;
    std::vector<std::vector<char>> map;
};
}  // namespace Map