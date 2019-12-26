#pragma once 

#include "curses.h"
#include "panel.h"

#include "Map/Map.h"
#include "OptionsInterface.h"
#include "Visual.h"
#include "GameObject/Subject.h"
#include "GameObject/Character.h"
#include "constants.h"
#include "Game.h"
#include "menu.h"
#include "GameObject/GameObject.h"
#include "Options.h"
#include "Factory.h"

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
    std::shared_ptr<Game::Game> game;
    
    menu.select();
    while (menu.getSelected() != MENU_EXIT) {
        switch (menu.getSelected())
        {
        case MENU_NEWGAME:
            game = std::shared_ptr<Game::Game>(new Game::Game());
            
            try {
                game->startNewGame();
            }
            catch (std::exception e) {
                Visual::showMessage(e.what());
            }
            break;
        
        case MENU_CONTINUE:
            game = std::shared_ptr<Game::Game>(new Game::Game());
            
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

    clear();
    refresh();
    endwin();
    return 0;
}


