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
                    
                    auto obj = factory->CreateGameObject(y, x);
                    delete factory;

                    objects.push_back(obj);
                    if (ch == 'H')
                        GameObject::hero = static_cast<GameObject::Hero*>(obj);
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
                if (filledCells.find({ y_, x_ }) == filledCells.end())
                    mvaddch(y + y_, x + x_, '.');
            }   
        }

        refresh();
    };

    void drawObjects(const std::vector<GameObject::GameObject*>& objects) {
        filledCells.clear();

        const int y = getYXForDrawing().first;
        const int x = getYXForDrawing().second;

        for (size_t i = 0; i < objects.size(); i++) {
            auto o = objects[i];
            mvaddch(y + o->getCoordY(), x + o->getCoordX(), o->getSymbOnMap());
            filledCells.emplace(o->getCoordY(), o->getCoordX());
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

    std::set<std::pair<int, int>> filledCells;
    std::vector<std::vector<char>> map;
};
}  // namespace Map