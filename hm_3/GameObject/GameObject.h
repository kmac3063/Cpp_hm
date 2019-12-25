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
protected:
    int y, x;
};
}  // namespace GameObject

//void collide(GameObject* obj);
//void collide(Hero* h);
//void collide(Zombie* z);
//void collide(Princess* p);
//void collide(Projectile* p);
//void collide(Dragon* d);
//void collide(Trap* t);
//void collide(Wall* w);
//void collide(Medkit* m);
//
//void doCollide(Hero* h);
//void doCollide(Zombie* z);
//void doCollide(Princess* p);
//void doCollide(Projectile* p);
//void doCollide(Dragon* d);
//void doCollide(Trap* t);
//void doCollide(Wall* w);
//void doCollide(Medkit* m);