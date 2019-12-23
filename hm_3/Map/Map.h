#pragma once
#include <vector>

namespace Map {
class Map {
 public:
    void readMapFromFile() {
        std::ifstream file(MAP_FILE_NAME);
        try {
            if (!file)
                throw;

            file >> height >> width;
            map.resize(height, std::vector<char>(width));

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    file >> map[y][x];
                }
            }

        }
        catch (std::exception e) {
            throw std::exception("The map file's, like, corrupted or something.");
        }


    }
    
    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    void drawMap() {
        const int y = getYXForDrawing().first;
        const int x = getYXForDrawing().second;

        for (int y_ = 0; y_ < height; y_++) {
            for (int x_ = 0; x_ < width; x_++) {
                mvaddch(y + y_, x + x_, map[y_][x_]);
            }   
        }

        refresh();
    };

    void drawObjects(const std::vector<GameObject::GameObject*>& objects) {
        const int y = getYXForDrawing().first;
        const int x = getYXForDrawing().second;

        for (int i = 0; i < objects.size(); i++) {
            auto o = objects[i];
            mvaddch(y + o->getCoordY(), x + o->getCoordX(), o->getSymbOnMap());
        }
        refresh();
    };

    std::pair<int, int> getYXForDrawing() {
        int maxX, maxY;
        getmaxyx(stdscr, maxY, maxX);
        return std::make_pair((maxY - height) / 2, (maxX - width) / 2);
    }

 private:
    int width;
    int height;
    std::vector<std::vector<char>> map;
};
}