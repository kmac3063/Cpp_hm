#pragma once

#include "curses.h"
#include "panel.h"

#include "Options.h"
#include "constants.h"
#include "Visual.h"

#include "OptionsInterface.h"

Options::Options::Options() {
    int height, width;
    getmaxyx(stdscr, height, width);
    y = (height - OPTIONS_HEIGHT) / 2;
    x = (width - OPTIONS_WIDTH) / 2;
}

void Options::Options::setDefault() {
    Dif = OPTIONS_EASY;
    TimerOn = true;
    RainOn = false;
}

void Options::Options::open() {
    clear();

    int x1 = x - 1;
    int x2 = x + OPTIONS_WIDTH;
    int y1 = y - 1;
    int y2 = y + OPTIONS_HEIGHT;


    bool exit = false;
    while (!exit) {
        drawOptions();
        Visual::drawBorder(y1, y2, x1, x2);
        if (RainOn)
            Visual::drawRain(y1, y2, x1, x2);

        switch (getch()) {
        case KEY_UP:
            if (--selected_id < 0)
                selected_id += OPTIONS_HEIGHT - 2;
            break;
        case KEY_DOWN:
            if (++selected_id == OPTIONS_HEIGHT - 2)
                selected_id = 0;
            break;
        case KEY_LEFT:
            clear();
            switch (selected_id) {
            case 0:
                Dif = OPTIONS_EASY;
                break;
            case 1:
                TimerOn = false;
                break;
            case 2:
                RainOn = false;
                break;
            }
            break;
        case KEY_RIGHT:
            clear();
            switch (selected_id) {
            case 0:
                Dif = OPTIONS_HARD;
                break;
            case 1:
                TimerOn = true;
                break;
            case 2:
                RainOn = true;
                break;
            }
            break;
        case KEY_ESCAPE_:
            exit = true;
            break;
        }
    }

    clear();
    refresh();
}

void Options::Options::drawOptions() {
    std::string difStr = "EASY", timerStr = "ON", rainStr = "ON";
    if (Dif == OPTIONS_HARD) difStr = "HARD";
    if (!TimerOn) timerStr = "OFF";
    if (!RainOn) rainStr = "OFF";

    std::string settings[] = {
        "Difficulty = " + difStr,
        "Show timer = " + timerStr,
        "Show rain = " + rainStr
    };

    mvaddstr(y, x, info1.c_str());
    mvaddstr(y + 1, x, info2.c_str());

    for (auto i = 0; i < OPTIONS_HEIGHT - 2; i++) {
        if (i == selected_id)
            mvaddch(y + 2 + i, x, '>');
        else
            mvaddch(y + 2 + i, x, ' ');

        mvaddstr(y + 2 + i, x + 1, settings[i].c_str());
    }

    refresh();
}
