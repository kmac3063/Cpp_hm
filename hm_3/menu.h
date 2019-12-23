#pragma once
#include "Visual.h"

namespace Menu {
class Menu {
public:
    Menu() {
        int height, width;
        getmaxyx(stdscr, height, width);
        y = (height - MENU_HEIGHT) / 2;
        x = (width - MENU_WIDTH) / 2;
    }

    void select() {
        Visual::drawBorder(y - 1, y + MENU_HEIGHT, x - 1, x + MENU_WIDTH);
        bool exit = false;

        while (!exit) {
            drawMenu();
            if (Options::RainOn)
                Visual::drawRain(y - 1, y + MENU_HEIGHT, x - 1, x + MENU_WIDTH);

            switch (getch())
            {
            case KEY_UP:
                if (--selected_id < 0 )
                    selected_id += MENU_HEIGHT;
                break;
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

    int getSelected() {
        return itemCode[selected_id];
    }

private:
    void drawMenu() {
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
    
    int x, y;
    int selected_id = 0;
    const char items[MENU_HEIGHT][MENU_WIDTH] = {
        "New game",
        "Continue",
        "Credit",
        "Options",
        "Exit",
    };
    const int itemCode[MENU_HEIGHT] = {
        MENU_NEWGAME,
        MENU_CONTINUE,
        MENU_CREDIT,
        MENU_OPTIONS,
        MENU_EXIT
    };

};
}

//namespace A {
//
//}
//
////bool bar() {
////    return A::foo();
////}
//
//namespace A {
//    class B {
//        friend bool foo();
//    };
//
//    bool foo() { return true; };
//}