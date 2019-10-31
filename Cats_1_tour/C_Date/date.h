#pragma once

#include <string>

class Date {
 private:
    int y, m, d;
    int toDays() const {
        int days = 0;
        for (int i = 0; i < y; i++)
            days += 365 + (i % 4 == 0 && i % 100 != 0 || i % 400 == 0);

        if (m > 2 && (y % 4 == 0 && y % 100 != 0 || y % 400 == 0))
            days++;

        for (int i = 1; i < m; i++) {
            if (i == 2)
                days += 28;
            else if (i == 1 || i == 3 || i == 5
                || i == 7 || i == 8 || i == 10 || i == 12)
                days += 31;
            else
                days += 30;
        }

        days += d;

        return days;
    }

 public:
    Date(const int& year, const int& month, const int& day) :
        y(year), m(month), d(day) {}

    inline bool IsLeap() const {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    std::string ToString() const {
        std::string S = "";

        if (d < 10) S += "0";
        S += std::to_string(d) + '.';

        if (m < 10) S += "0";
        S += std::to_string(m) + '.';

        for (int i = 1; i <= 3; i++)
            if (y < pow(10, i)) S += "0";
        S += std::to_string(y);

        return S;
    }

    Date DaysLater(int days) const {
        Date t(y, m, d);

        while (days > 0) {
            if (t.m == 1 || t.m == 3 || t.m == 5
                || t.m == 7 || t.m == 8 || t.m == 10 || t.m == 12) {
                if (t.d == 31) {
                    t.m++;
                    t.d = 1;
                } else {
                    t.d++;
                }
            } else if (t.m == 2) {
                int leapDay = (t.y % 4 == 0 && t.y % 100 != 0)
                    || (t.y % 400 == 0);
                if (t.d == 28 + leapDay) {
                    t.m++;
                    t.d = 1;
                } else {
                    t.d++;
                }
            } else {
                if (t.d == 30) {
                    t.m++;
                    t.d = 1;
                } else {
                    t.d++;
                }
            }

            days--;
            if (t.m > 12) {
                t.y++;
                t.m = 1;
            }
        }

        return t;
    }

    int DaysLeft(const Date& date) const {
        return abs(toDays() - date.toDays());
    }
};
