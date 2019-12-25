#pragma once
#include <string>

namespace Visual {
    void drawBorder(const int& y1, const int& y2,
        const int& x1, const int& x2);

    void drawRain(const int& y1, const int& y2,
        const int& x1, const int& x2);

    void showMessage(std::string message);

    void drawTimer(const int& y, const int& x, const time_t& seconds);
}  // namespace Visual