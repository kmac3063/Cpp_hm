#pragma once

#include <memory>
#include <vector>
#include <fstream>
#include <string>

#include "../constants.h"
#include "../curses.h"
#include "../panel.h"
#include "../Factory.h"
#include "../GameObject/Character.h"

#include "Map.h"

void Map::Map::readMapFromFile(const int& levelId, 
        std::vector<std::shared_ptr<GameObject::GameObject>>& objects) {
    
    const std::string& fileName = "Map/level" + std::to_string(levelId) + ".map";

    try {
        std::ifstream file(fileName);
        if (!file)
            throw;

        file >> height >> width >> levelRequiredScore;
        map.resize(height, std::vector<char>(width));

        std::shared_ptr<Factory::Factory> factory;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                char ch;
                file >> ch;

                if (ch == '.')
                    continue;

                switch (ch) {
                case 'H': {
                    factory = std::shared_ptr<Factory::Factory>(new Factory::FactoryHero());
                    break;
                }
                case 'P':
                    factory = std::shared_ptr<Factory::Factory>(new Factory::FactoryPrincess());
                    break;
                case 'Z':
                    factory = std::shared_ptr<Factory::Factory>(new Factory::FactoryZombie());
                    break;
                case 'D':
                    factory = std::shared_ptr<Factory::Factory>(new Factory::FactoryDragon());
                    break;
                case 'T':
                    factory = std::shared_ptr<Factory::Factory>(new Factory::FactoryTrap());
                    break;
                case '#':
                    factory = std::shared_ptr<Factory::Factory>(new Factory::FactoryWall());
                    break;
                case '+':
                    factory = std::shared_ptr<Factory::Factory>(new Factory::FactoryMedkit());
                    break;
                }

                auto obj = factory->CreateGameObject(y, x);
                
                objects.push_back(obj);
                if (ch == 'H') {
                    GameObject::hero = 
                        std::shared_ptr<GameObject::Hero>(static_cast<GameObject::Hero*>(obj.get()));
                }
            }
        }

    }
    catch (std::exception e) {
        throw std::exception("The map file's, like, corrupted or something.");
    }
}

int Map::Map::getWidth() {
    return width;
}

int Map::Map::getHeight() {
    return height;
}

void Map::Map::drawMap() {
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

void Map::Map::drawObjects(const std::vector<std::shared_ptr<GameObject::GameObject>>& objects) {
    filledCells.clear();

    const int y = getYXForDrawing().first;
    const int x = getYXForDrawing().second;

    for (size_t i = 0; i < objects.size(); i++) {
        auto o = objects[i];
        if (!o->isAlive())
            continue;
        mvaddch(y + o->getCoordY(), x + o->getCoordX(), o->getSymbOnMap());
        filledCells.emplace(o->getCoordY(), o->getCoordX());
    }

    refresh();
};

std::pair<int, int> Map::Map::getYXForDrawing() {
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);

    return std::make_pair((maxY - height) / 2, (maxX - width) / 2);
}

int Map::Map::getLevelRequiredScore() {
    return levelRequiredScore;
}