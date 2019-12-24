#pragma once


namespace GameObject {

std::map<char, int> HP_TABLE;
std::map<char, int> DMG_TABLE;
std::map<char, int64_t> SLEEPTIME_TABLE;

class GameObject {
public:
    virtual char getSymbOnMap() = 0;
    
    void setPos(const int& y_, const int& x_) {
        y = y_;
        x = x_;
    }
    int getCoordY() { return y; }
    int getCoordX() { return x; }

    virtual void update(GameObject*& refObj) {};

protected:
    int y, x;
};
}  // namespace GameObject