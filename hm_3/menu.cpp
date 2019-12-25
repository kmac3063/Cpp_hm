#pragma once

#include "panel.h"
#include "curses.h"

#include "menu.h"
#include "Visual.h"
#include "Options.h"

Menu::Menu::Menu() {
    int height, width;
    getmaxyx(stdscr, height, width);
    y = (height - MENU_HEIGHT) / 2;
    x = (width - MENU_WIDTH) / 2;
}

void Menu::Menu::select() {
    Visual::drawBorder(y - 1, y + MENU_HEIGHT, x - 1, x + MENU_WIDTH);
    bool exit = false;

    while (!exit) {
        drawMenu();
        if (Options::RainOn)
            Visual::drawRain(y - 1, y + MENU_HEIGHT, x - 1, x + MENU_WIDTH);

        switch (getch())
        {
        case 'w':
        case 'W':
        case KEY_UP:
            if (--selected_id < 0)
                selected_id += MENU_HEIGHT;
            break;

        case 's':
        case 'S':
        case KEY_DOWN:
            if (++selected_id == MENU_HEIGHT)
                selected_id = 0;
            break;
        case KEY_ESCAPE_:
            selected_id = 4;
        case KEY_ENTER_:
            exit = true;
            break;
        }
    }
}

int Menu::Menu::getSelected() {
    return itemCode[selected_id];
}

void Menu::Menu::drawMenu() {
    for (int i = 0; i < MENU_HEIGHT; i++)
    {
        if (i == selected_id)
            mvaddch(y + i, x, '>');
        else
            mvaddch(y + i, x, ' ');

        mvprintw(y + i, x + 1, "%s", items[i]);
    }
    refresh();
}

