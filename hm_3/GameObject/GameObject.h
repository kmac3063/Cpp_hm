#pragma once


namespace GameObject {

std::map<char, int> HP_TABLE;
std::map<char, int> DMG_TABLE;

class GameObject {
public:
    virtual char getSymbOnMap() = 0;
    
    void setPos(const int& y_, const int& x_) {
        y = y_;
        x = x_;
    }

    virtual int getCoordX() { return x; }
    virtual int getCoordY() { return y; }
protected:
    int x, y;
};
}  // namespace GameObject