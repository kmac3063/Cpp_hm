#pragma once

class Options {
public:
    void open(int windowHeight, int windowWidth) {
        clear();

        const std::string info1 = "To change Press '<-' or '->'";
        const std::string info2 = "To exit, press 'ESC'";
        const std::string settings[] = {"Difficulty = " + dif};

        int x1 = (windowWidth - OPTIONS_WIDTH) / 2 - 1;
        int x2 = x1 + OPTIONS_WIDTH + 1;
        int y1 = (windowHeight + OPTIONS_HEIGHT) / 2 - 1;
        int y2 = y1 + OPTIONS_HEIGHT + 1;

        Visual::drawBorder(y1, y2, x1, x2);
        mvaddstr(y1 + 1, x1 + 1, info1.c_str());
        mvaddstr(y1 + 2, x1 + 1, info2.c_str());
        for (auto i = 0; i < OPTIONS_HEIGHT - 2; i++) {
            if (i == selected_id)
                mvaddch(y1 + 3 + i, x1 + 1, '>');
            else
                mvaddch(y1 + 3 + i, x1 + 1, ' ');

            mvaddstr(y1 + 3 + i, x1 + 2, settings[i].c_str());
        }

        char g;
        while ((g = getch()) != KEY_ESCAPE_) {
            Visual::drawRain(y1, y2, x1, x2);

            switch (g) {
            case KEY_UP:
                if (--selected_id < 0)
                    selected_id += OPTIONS_HEIGHT - 2;
                break;
            case KEY_DOWN:
                if (++selected_id == OPTIONS_HEIGHT - 2)
                    selected_id = 0;
                break;
            case KEY_LEFT:
                // Изменить ИЗИ на число, чтобы в других настройках мог менять нормально.
            }
        }

        refresh();
        clear();
    }

private:
    int selected_id = 0;
    std::string dif = "EASY";
};