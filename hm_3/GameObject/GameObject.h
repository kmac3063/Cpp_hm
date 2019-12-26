#pragma once

#include <memory>
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

extern std::shared_ptr<Hero> hero;
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

    virtual void update(std::shared_ptr<GameObject>& refObj) = 0;

    virtual void collide(std::shared_ptr<GameObject>) = 0;
    virtual void collide(std::shared_ptr<Hero>) = 0;
    virtual void collide(std::shared_ptr<Zombie>) = 0;
    virtual void collide(std::shared_ptr<Princess>) = 0;
    virtual void collide(std::shared_ptr<Projectile>) = 0;
    virtual void collide(std::shared_ptr<Dragon>) = 0;
    virtual void collide(std::shared_ptr<Trap>) = 0;
    virtual void collide(std::shared_ptr<Wall>) = 0;
    virtual void collide(std::shared_ptr<Medkit>) = 0;
protected:
    int y = 0, x = 0;
};
}  // namespace GameObject
