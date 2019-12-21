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
        Sleep(40);

        for (auto p : xy) {
            mvaddch(p.y, p.x, ' ');
        }
    }
}