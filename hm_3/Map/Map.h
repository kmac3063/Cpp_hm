#pragma once

#include <set>
#include <vector>

#include "../GameObject/GameObject.h"

namespace Map {
class Map {
 public:
    void readMapFromFile(const int& levelId, std::vector<std::shared_ptr<GameObject::GameObject>>& objects);
    
    int getWidth();

    int getHeight();

    void drawMap();

    void drawObjects(const std::vector<std::shared_ptr<GameObject::GameObject>>&);

    std::pair<int, int> getYXForDrawing();

    int getLevelRequiredScore();

 private:
    int width = 0;
    int height = 0;
    int levelRequiredScore = 0;

    std::set<std::pair<int, int>> filledCells;
    std::vector<std::vector<char>> map;
};
}  // namespace Map