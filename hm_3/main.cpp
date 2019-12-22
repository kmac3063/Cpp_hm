#include <iostream>
#include <algorithm>
#include <string>
#include <thread>
#include <Windows.h>#include <vector>
#include <fstream>

#include "curses.h"
#include "panel.h"

#include "constants.h"
#include "menu.h"
#include "Visual.h"
#include "Options.h"
#include "Game.h"

void showMessage(std::string message) {
    clear();
    int windowHeight, windowWidth;
    getmaxyx(stdscr, windowHeight, windowWidth);

    int x1 = (windowWidth - message.length()) / 2 - 1;
    int x2 = x1 + message.length() + 1;
    int y1 = windowHeight / 2 - 1;
    int y2 = windowHeight / 2 + 1;

    Visual::drawBorder(y1, y2, x1, x2);
    mvaddstr(y1 + 1, x1 + 1, message.c_str());

    while (getch() == ERR)
        Visual::drawRain(y1, y2, x1, x2);

    refresh();
    clear();
}

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

    Menu menu;
    Options options;
    Game* game = nullptr;
    auto configFileName = "Config/Config.cfg";
    auto saveFileName = "Save/Save.save";

    menu.select();
    while (menu.getSelected() != MENU_EXIT) {
        switch (menu.getSelected())
        {
        case MENU_NEWGAME:
            game = new Game(options);
            
            game->startGame();
            break;
        
        case MENU_CONTINUE:
            game = new Game(options);
            if (game->loadSaveFromFile(saveFileName)) {
                game->startGame();
            }
            else {
                showMessage("The save file's, like, corrupted or something.");
            }
            break;

        case MENU_CREDIT:
            showMessage("Creator: Lancov Igor");
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