#pragma once
#include <vector>

namespace Map {
class Map {
 public:
    auto readMapFromFile(std::vector<GameObject::GameObject*>& objects) {
        std::ifstream file(MAP_FILE_NAME);

        try {
            if (!file)
                throw;

            file >> height >> width;
            map.resize(height, std::vector<char>(width));

            Factory::Factory* factory = nullptr;

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    char ch;
                    file >> ch;

                    if (ch == '.')
                        continue;

                    switch (ch) {
                    case 'H':
                        factory = new Factory::FactoryHero();
                        break;
                    case 'P':
                        factory = new Factory::FactoryPrincess();
                        break;
                    case 'Z':
                        factory = new Factory::FactoryZombie();
                        break;
                    case 'D':
                        factory = new Factory::FactoryDragon();
                        break;
                    case 'T':
                        factory = new Factory::FactoryTrap();
                        break;
                    case '#':
                        factory = new Factory::FactoryWall();
                        break;
                    case '+':
                        factory = new Factory::FactoryMedkit();
                        break;
                    }

                    objects.push_back(factory->CreateGameObject(y, x));
                    delete factory;
                }
            }

        }
        catch (std::exception e) {
            throw std::exception("The map file's, like, corrupted or something.");
        }

        return objects;
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
                mvaddch(y + y_, x + x_, '.');
            }   
        }

        refresh();
    };

    void drawObjects(const std::vector<GameObject::GameObject*>& objects) {
        const int y = getYXForDrawing().first;
        const int x = getYXForDrawing().second;
        
        // запоминаем координаты, в которых есть монстры, карту в них не рисуем.

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