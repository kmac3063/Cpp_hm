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

        GameObject::Hero* hero = new GameObject::Hero();
        hero->setPos(5, 5);
        map->addObjOnMap(hero);

        bool gameOn = true;
        while (gameOn) {
            int maxX, maxY;
            getmaxyx(stdscr, maxY, maxX);
            int x1 = (maxX - map->getWidth()) / 2;
            int y1 = (maxY - map->getHeight()) / 2;
            int x2 = x1 + map->getWidth();
            int y2 = y1 + map->getHeight();
            Visual::drawBorder(y1 - 1, y2, x1 - 1, x2);

            if (Options::RainOn)
                Visual::drawRain(y1 - 1, y2, x1 - 1, x2);
            if (Options::TimerOn) {}
                //Visual::drawTimer();
            //drawInterface();
            map->drawMap();
            map->drawObjects();
            
            switch (getch()) {
            case KEY_LEFT:
            case 'a':
            case 'A':
                hero->move(0, -1);
                break;

            case KEY_UP:
            case 'w':
            case 'W':
                hero->move(-1, 0);
                break;

            case KEY_RIGHT:
            case 'd':
            case 'D':
                hero->move(0, 1);
                break;

            case KEY_DOWN:
            case 's':
            case 'S':
                hero->move(1, 0);
                break;

            case ' ':
                //спавн прожектайл и двигаем его по move(dirX, dirY);
                break;

            case KEY_ESCAPE_:
                //save in file
                gameOn = false;
                break;
            }
            
            /*updateCharacters();
            collideAll();*/
        }

        clear();
    }
private:
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
                int hp, dmg;
                
                file >> ch >> hp >> dmg;
                
                GameObject::HP_TABLE[ch] = hp; 
                GameObject::DMG_TABLE[ch] = dmg;
            }

            if (GameObject::HP_TABLE.size() != n_obj)
                throw;
        }
        catch (std::exception e) {
            throw std::exception("The config file's, like, corrupted or something.");
        }
        
    }

    void readMap()  {
        try {
            map->readMapFromFile();
        }
        catch (std::exception e) {
            throw;
        }
    }

    Map::Map* map;
};
}