#pragma once
#include <string>

namespace Visual {
    void drawBorder(const int& y1, const int& y2,
        const int& x1, const int& x2);

    void drawRain(const int& y1, const int& y2,
        const int& x1, const int& x2);

    void showMessage(const std::string& message, const int& delaySec = 0);

    void drawTimer(const int& y, const int& x, const int& seconds);
}  // namespace Visual