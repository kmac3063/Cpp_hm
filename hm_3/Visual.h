#pragma once

namespace Visual {

    void drawBorder(const int& y1, const int& y2, 
                    const int& x1, const int& x2) {
        for (int x = x1; x <= x2; x++) {
            mvaddch(y1, x, '-');
            mvaddch(y2, x, '-');
        }
        for (int y = y1 + 1; y <= y2 - 1; y++) {
            mvaddch(y, x1, '|');
            mvaddch(y, x2, '|');
        }

    }

    void drawRain(const int& y1, const int& y2,
                const int& x1, const int& x2) {
        int maxX, maxY;
        getmaxyx(stdscr, maxY, maxX);

        struct Coord { int x, y; };
        Coord xy[100];

        for (int i = 0; i < 100; i++)
        {
            int rX = rand() % maxX;
            int rY = rand() % maxY;

            while (x1 <= rX && rX <= x2
                && y1 <= rY && rY <= y2) {
                rX = rand() % maxX;
                rY = rand() % maxY;
            }

            mvaddch(rY, rX, '|' | A_UNDERLINE);
            xy[i] = { rX, rY };
        }
        refresh();
        
        if (clock() % 20) // Ёффект прибывающего дожд€
            for (auto p : xy) 
                mvaddch(p.y, p.x, ' ');
    }

    void showMessage(std::string message) {
        clear();
        int windowHeight, windowWidth;
        getmaxyx(stdscr, windowHeight, windowWidth);

        int x1 = (windowWidth - message.length()) / 2 - 1;
        int x2 = x1 + message.length() + 1;
        int y1 = windowHeight / 2 - 1;
        int y2 = windowHeight / 2 + 1;

        drawBorder(y1, y2, x1, x2);
        mvaddstr(y1 + 1, x1 + 1, message.c_str());

        while (getch() == ERR) {
            drawRain(y1, y2, x1, x2);
        }

        refresh();
        clear();
    }

    void drawTimer(const int& y, const int& x, const time_t& seconds) {
        int minut = seconds / 60;
        int sec = seconds - minut * 60;
        std::string S = "";
        if (minut < 10)
            S += '0';
        S += std::to_string(minut) + " : ";
        if (sec < 10)
            S += '0';
        S += std::to_string(sec);

        mvaddstr(y, x, S.c_str());
    }
}