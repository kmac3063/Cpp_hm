#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <thread>
#include <Windows.h>
#include "curses.h"
#include "panel.h"

#include "Options.h"
#include "constants.h"
#include "menu.h"
#include "Visual.h"
#include "OptionsInterface.h"

#include "GameObject/GameObject.h"
#include "GameObject/Character.h"
#include "GameObject/Subject.h"
#include "Factory.h"
#include "Map/Map.h"
#include "Game.h"

void init_() {
    initscr();
    noecho();
    keypad(stdscr, true);
    curs_set(0);
    nodelay(stdscr, TRUE);
}

int main() {
    init_();

    int windowHeight, windowWidth;
    getmaxyx(stdscr, windowHeight, windowWidth);

    Menu::Menu menu;
    Options::Options options;
    options.setDefault();
    Game::Game* game = nullptr;

    menu.select();
    while (menu.getSelected() != MENU_EXIT) {
        switch (menu.getSelected())
        {
        case MENU_NEWGAME:
            game = new Game::Game();
            
            try {
                game->startGame();
            }
            catch (std::exception e) {
                Visual::showMessage(e.what());
            }
            break;
        
        case MENU_CONTINUE:
            game = new Game::Game();
            
            try {
                game->loadSaveFile();
                game->startGame();
            } 
            catch (std::exception e) {
                Visual::showMessage(e.what());
            }

            break;

        case MENU_CREDIT:
            Visual::showMessage("Creator: Lancov Igor");
            break;

        case MENU_OPTIONS:
            options.open();
            break;
        }
        menu.select();
    }

    if (game != nullptr)
        delete game;

    clear();
    refresh();
    endwin();
    return 0;
}


