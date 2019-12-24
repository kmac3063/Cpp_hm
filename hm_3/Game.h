#pragma once
#include <fstream>
#include <vector>

namespace Game {
class Game {
public:
    ~Game() {
        if (map != nullptr)
            delete map;
    }

    void loadSaveFile() {
        std::ifstream file(CONFIG_FILE_NAME);
        if (!file)
            throw std::exception("The save file's, like, corrupted or something.");
    }

    void startGame()  {
        clear();
        try {
            init();
        }
        catch (std::exception e) {
            if (map != nullptr)
                delete map;
            throw;
        }

        hero = new GameObject::Hero();
        hero->setPos(5, 5);
        objects.push_back(hero);

        startTime = time(NULL);
        
        bool gameOn = true;
        while (gameOn && hero->live()) {
            drawAll();

            switch (getch()) {
            case KEY_LEFT:
            case 'a':
            case 'A':
                hero->dir(0, -1);
                break;

            case KEY_UP:
            case 'w':
            case 'W':
                hero->dir(-1, 0);
                break;

            case KEY_RIGHT:
            case 'd':
            case 'D':
                hero->dir(0, 1);
                break;

            case KEY_DOWN:
            case 's':
            case 'S':
                hero->dir(1, 0);
                break;

            case ' ': {
                hero->doShot();
            }
            break;

            case KEY_ESCAPE_:
                //save in file
                gameOn = false;
                break;
            }
            
            updateObjects();

            collideObjects();
        }

        if (!hero->live()) {
            hero->showDieMessage();
        }

        clear();
    }
private:
    void drawAll() {
        int maxX, maxY;
        getmaxyx(stdscr, maxY, maxX);

        int x1 = (maxX - map->getWidth()) / 2;
        int y1 = (maxY - map->getHeight()) / 2;
        int x2 = x1 + map->getWidth();
        int y2 = y1 + map->getHeight();

        Visual::drawBorder(y1 - 2, y2 + 1, x1 - 3, x2 + 2);

        if (Options::RainOn)
            Visual::drawRain(y1 - 2, y2 + 1, x1 - 3, x2 + 2);
        if (Options::TimerOn) {
            time_t elapsedTime = time(NULL) - startTime;
            Visual::drawTimer(y1 - 1, x1, elapsedTime);
        }
        
        map->drawMap();
        drawInterface(y2, x1);
        map->drawObjects(objects);
    }

    void drawInterface(const int& y, const int& x) {
        auto hpStr = std::to_string(hero->getHP());
        auto scoreStr = std::to_string(hero->getScore());
        mvaddstr(y, x, ("HP : " + hpStr + " SCORE : " + scoreStr).c_str());
        refresh();
    }


    void init() {
        map = new Map::Map();
        try {
            readConfig();
            readMap();
        }
        catch(std::exception e) {
            throw;
        }
    }

    void readConfig() {
        std::ifstream file(CONFIG_FILE_NAME);

        try {
            if (!file)
                throw;
            
            int n_obj;
            file >> n_obj;
            for (int i = 0; i < n_obj; i++) {
                char ch;
                int hp, dmg, sleepTms;
                
                file >> ch;

                if (ch == '#')
                    continue;
                if (ch == '+') {
                    file >> hp;
                    GameObject::HP_TABLE[ch] = hp;
                    continue;
                }
                
                file >> hp >> dmg >> sleepTms;

                GameObject::HP_TABLE[ch] = hp; 
                GameObject::DMG_TABLE[ch] = dmg;
                GameObject::SLEEPTIME_TABLE[ch] = sleepTms;
            }
        }
        catch (std::exception e) {
            throw std::exception("The config file's, like, corrupted or something.");
        }
        
    }

    void readMap()  {
        try {
             map->readMapFromFile(objects);
        }
        catch (std::exception e) {
            throw;
        }
    }

    void updateObjects() {
        GameObject::GameObject* newObj = nullptr;
        std::vector<GameObject::GameObject*> newObjects;
        for (auto o : objects) {
            o->update(newObj);
            
            if (newObj != nullptr) {
                newObjects.push_back(newObj);
            }

            newObj = nullptr;
        }

        for (int i = 0; i < newObjects.size(); i++)
            objects.push_back(newObjects[i]);
    }

    void collideObjects() {
        for (int i = 0; i < objects.size() - 1; i++) {
            for (int j = i + 1; j < objects.size(); j++) {
                if (objects[i]->getCoordX() == objects[j]->getCoordX()
                    && objects[i]->getCoordY() == objects[j]->getCoordY()){
                    //objects[i].collide(objects[j]);
                }
            }
        }
    }

    time_t startTime;

    std::vector<GameObject::GameObject*> objects;
    Map::Map* map;

    GameObject::Hero* hero;
};
}