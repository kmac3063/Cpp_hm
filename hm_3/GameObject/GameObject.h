#pragma once
#include <map>

namespace GameObject {
class Hero;
class Zombie;
class Dragon;
class Princess;
class Projectile;
class Trap;
class Wall;
class Medkit;

extern Hero* hero;
extern std::map<char, int> HP_TABLE;
extern std::map<char, int> DMG_TABLE;
extern std::map<char, int64_t> SLEEPTIME_TABLE;

class GameObject {
public:
    virtual char getSymbOnMap() = 0;
    
    void setPos(const int& y_, const int& x_);
    int getCoordY();
    int getCoordX();

    virtual bool isAlive() = 0;

    virtual void update(GameObject*& refObj) = 0;

    virtual void collide(GameObject*) = 0;
    virtual void collide(Hero*) = 0;
    virtual void collide(Zombie*) = 0;
    virtual void collide(Princess*) = 0;
    virtual void collide(Projectile*) = 0;
    virtual void collide(Dragon*) = 0;
    virtual void collide(Trap*) = 0;
    virtual void collide(Wall*) = 0;
    virtual void collide(Medkit*) = 0;
protected:
    int y = 0, x = 0;
};
}  // namespace GameObject
