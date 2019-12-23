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
        int a = 2;
        GameObject::Hero* hero = new GameObject::Hero();
        hero->setPos(5, 5);

        characters.push_back(hero);
        objects.push_back(hero);

        time_t startTime = time(NULL);
        bool gameOn = true;
        while (gameOn && hero->live()) {
            int maxX, maxY;
            getmaxyx(stdscr, maxY, maxX);
            
            int x1 = (maxX - map->getWidth()) / 2;
            int y1 = (maxY - map->getHeight()) / 2;
            int x2 = x1 + map->getWidth();
            int y2 = y1 + map->getHeight();

            Visual::drawBorder(y1 - 2, y2 + 1, x1 - 2, x2 + 2);

            if (Options::RainOn)
                Visual::drawRain(y1 - 2, y2 + 1, x1 - 2, x2 + 2);
            if (Options::TimerOn) {
                time_t elapsedTime = time(NULL) - startTime;
                Visual::drawTimer(y1 - 1, x1, elapsedTime);
            }
            //drawInterface();
            map->drawMap();
            map->drawObjects(objects);
            
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
                GameObject::Projectile* bullet = new GameObject::Projectile();

                int heroX = hero->getCoordX();
                int heroY = hero->getCoordY();

                int herody = hero->getLastDir().first;
                int herodx = hero->getLastDir().second;

                bullet->dir(herody, herodx);
                bullet->setPos(heroY + herody, heroX + herodx);

                characters.push_back(bullet);
                objects.push_back(bullet);
            }
            break;

            case KEY_ESCAPE_:
                //save in file
                gameOn = false;
                break;
            }
            
            updateCharactersLoc();
            collideAll();
        }

        if (!hero->live()) {
            hero->showDieMessage();
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
                int hp, dmg, sleepTms;
                
                file >> ch >> hp >> dmg >> sleepTms;
                
                GameObject::HP_TABLE[ch] = hp; 
                GameObject::DMG_TABLE[ch] = dmg;
                GameObject::SPEEPTIME_TABLE[ch] = sleepTms;
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

    void updateCharactersLoc() {
        for (GameObject::Character* o : characters) {
            o->move();
        }
    }

    void collideAll() {

    }

    std::vector<GameObject::GameObject*> objects;
    std::vector<GameObject::Character*> characters;
    Map::Map* map;
};
}