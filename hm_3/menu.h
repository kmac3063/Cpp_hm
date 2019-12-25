#pragma once

#include "constants.h"

namespace Menu {
class Menu {
public:
    Menu();

    void select();

    int getSelected();

private:
    void drawMenu();
    
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
}  // namespace Menu