#include <iostream>
#include <algorithm>
#include <string>
#include <thread>
#include <Windows.h>

#include "curses.h"
#include "panel.h"

#include "constants.h"
#include "menu.h"
#include "Visual.h"
#include "Options.h"

void showCredit(int windowHeight, int windowWidth) {
    clear();
    const std::string creatorName = "Creator: Lancov Igor";
    
    int x1 = (windowWidth - creatorName.length()) / 2 - 1;
    int x2 = x1 + creatorName.length() + 1;
    int y1 = windowHeight / 2 - 1;
    int y2 = windowHeight / 2 + 1;

    Visual::drawBorder(y1, y2, x1, x2);
    mvaddstr(y1 + 1, x1 + 1, creatorName.c_str());

    while (getch() == ERR)
        Visual::drawRain(y1, y2, x1, x2);

    refresh();
    clear();
}

int main() {
    initscr();
    noecho();
    keypad(stdscr, true);
    curs_set(0);
    nodelay(stdscr, TRUE);

    int windowHeight, windowWidth;
    
    getmaxyx(stdscr, windowHeight, windowWidth);

    Menu menu(windowHeight, windowWidth);
    Options options;

    menu.select();
    while (menu.getSelected() != MENU_EXIT) {
        switch (menu.getSelected())
        {
        case MENU_NEWGAME:
            /*Game game;
            game.startNewGame();*/
            break;
        case MENU_CONTINUE:
            /*Game game;
            Save save;
            std::string fileName;
            try {
                scanw("%s", &fileName);
                save.loadFromFile(fileName);
            }
            catch (std::exception e){
                printw("File \"%s\" not found or corrupt.", fileName);
                continue;
            }
            game.start(save);*/
            break;
        case MENU_CREDIT:
            showCredit(windowHeight, windowWidth);
            break;
        case MENU_OPTIONS:
            options.open(windowHeight, windowWidth);
            break;
        }
        menu.select();
    }

    clear();
    endwin();
    return 0;
}