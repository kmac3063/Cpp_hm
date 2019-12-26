#pragma once

#include "GameObject.h"
#include "../constants.h"

namespace GameObject {
class Character : public GameObject {
public:
    Character(const int& HP, const int& Dmg, const int64_t& SleepTimeMs);
    virtual void dir(const int& dy_, const int& dx_);
    
    void setHP(const int& hp_);
    int getHP();

    void damage(const int& damage);
    int getDamagePower();
    void heal(const int& heal);
    virtual bool isAlive();

    virtual void update(std::shared_ptr<GameObject>& refObj);

    void getLastDir(int& dy, int& dx);

protected:
    virtual void move();

    int64_t sleepTimeMs;
    int64_t lastUseMs = 0;
    int64_t lastDmgMs = 0;
    std::pair<int, int> lastDir = { 0, 0 };

    int hp, dmg;
    int dx = 0, dy = 0;
};


class Friendly : public Character {
public:
    Friendly(const int& HP, const int& Dmg, const int64_t& SleepTimeMs);
};

class Princess : public Friendly {
public:
    Princess();

    virtual char getSymbOnMap();

    virtual void collide(std::shared_ptr<GameObject>);
    virtual void collide(std::shared_ptr<Hero>);
    virtual void collide(std::shared_ptr<Zombie>);
    virtual void collide(std::shared_ptr<Princess>);
    virtual void collide(std::shared_ptr<Projectile>);
    virtual void collide(std::shared_ptr<Dragon>);
    virtual void collide(std::shared_ptr<Trap>);
    virtual void collide(std::shared_ptr<Wall>);
    virtual void collide(std::shared_ptr<Medkit>);

    void doCollide(std::shared_ptr<Hero>);
    void doCollide(std::shared_ptr<Zombie>);
    void doCollide(std::shared_ptr<Princess>);
    void doCollide(std::shared_ptr<Projectile>);
    void doCollide(std::shared_ptr<Dragon>);
    void doCollide(std::shared_ptr<Trap>);
    void doCollide(std::shared_ptr<Wall>);
    void doCollide(std::shared_ptr<Medkit>);

};


class Enemy : public Character {
public:
    Enemy(const int& HP, const int& Dmg, const int64_t& SleepTimeMs);
};

class Projectile : public Enemy {
public:
    Projectile();

    virtual void dir(const int& dy_, const int& dx_);

    virtual char getSymbOnMap();

    virtual void collide(std::shared_ptr<GameObject>);
    virtual void collide(std::shared_ptr<Hero>);
    virtual void collide(std::shared_ptr<Zombie>);
    virtual void collide(std::shared_ptr<Princess>);
    virtual void collide(std::shared_ptr<Projectile>);
    virtual void collide(std::shared_ptr<Dragon>);
    virtual void collide(std::shared_ptr<Trap>);
    virtual void collide(std::shared_ptr<Wall>);
    virtual void collide(std::shared_ptr<Medkit>);

    void doCollide(std::shared_ptr<Hero>);
    void doCollide(std::shared_ptr<Zombie>);
    void doCollide(std::shared_ptr<Princess>);
    void doCollide(std::shared_ptr<Projectile>);
    void doCollide(std::shared_ptr<Dragon>);
    void doCollide(std::shared_ptr<Trap>);
    void doCollide(std::shared_ptr<Wall>);
    void doCollide(std::shared_ptr<Medkit>);

private:
    virtual void move();
};

class Dragon : public Enemy{
public:
    Dragon();
    
    virtual char getSymbOnMap();

    virtual void update(std::shared_ptr<GameObject>& refObj);

    void damage(const int& damage);

    virtual void collide(std::shared_ptr<GameObject>);
    virtual void collide(std::shared_ptr<Hero>);
    virtual void collide(std::shared_ptr<Zombie>);
    virtual void collide(std::shared_ptr<Princess>);
    virtual void collide(std::shared_ptr<Projectile>);
    virtual void collide(std::shared_ptr<Dragon>);
    virtual void collide(std::shared_ptr<Trap>);
    virtual void collide(std::shared_ptr<Wall>);
    virtual void collide(std::shared_ptr<Medkit>);

    void doCollide(std::shared_ptr<Hero>);
    void doCollide(std::shared_ptr<Zombie>);
    void doCollide(std::shared_ptr<Princess>);
    void doCollide(std::shared_ptr<Projectile>);
    void doCollide(std::shared_ptr<Dragon>);
    void doCollide(std::shared_ptr<Trap>);
    void doCollide(std::shared_ptr<Wall>);
    void doCollide(std::shared_ptr<Medkit>);

private:
    int64_t lastShotTime = 0;
    std::shared_ptr<Projectile> shot(const int& dy, const int& dx);
};

class Zombie : public Enemy {
public:
    Zombie();

    virtual char getSymbOnMap();

    virtual void update(std::shared_ptr<GameObject>& refObj);

    void damage(const int& damage);

    virtual void collide(std::shared_ptr<GameObject>);
    virtual void collide(std::shared_ptr<Hero>);
    virtual void collide(std::shared_ptr<Zombie>);
    virtual void collide(std::shared_ptr<Princess>);
    virtual void collide(std::shared_ptr<Projectile>);
    virtual void collide(std::shared_ptr<Dragon>);
    virtual void collide(std::shared_ptr<Trap>);
    virtual void collide(std::shared_ptr<Wall>);
    virtual void collide(std::shared_ptr<Medkit>);

    void doCollide(std::shared_ptr<Hero>);
    void doCollide(std::shared_ptr<Zombie>);
    void doCollide(std::shared_ptr<Princess>);
    void doCollide(std::shared_ptr<Projectile>);
    void doCollide(std::shared_ptr<Dragon>);
    void doCollide(std::shared_ptr<Trap>);
    void doCollide(std::shared_ptr<Wall>);
    void doCollide(std::shared_ptr<Medkit>);
};

class Trap : public Enemy {
public:
    Trap();

    virtual void collide(std::shared_ptr<GameObject>);
    virtual void collide(std::shared_ptr<Hero>);
    virtual void collide(std::shared_ptr<Zombie>);
    virtual void collide(std::shared_ptr<Princess>);
    virtual void collide(std::shared_ptr<Projectile>);
    virtual void collide(std::shared_ptr<Dragon>);
    virtual void collide(std::shared_ptr<Trap>);
    virtual void collide(std::shared_ptr<Wall>);
    virtual void collide(std::shared_ptr<Medkit>);
    
    void doCollide(std::shared_ptr<Hero>);
    void doCollide(std::shared_ptr<Zombie>);
    void doCollide(std::shared_ptr<Princess>);
    void doCollide(std::shared_ptr<Projectile>);
    void doCollide(std::shared_ptr<Dragon>);
    void doCollide(std::shared_ptr<Trap>);
    void doCollide(std::shared_ptr<Wall>);
    void doCollide(std::shared_ptr<Medkit>);

    virtual char getSymbOnMap();
};


class Hero : public Character {
public:
    Hero();

    virtual char getSymbOnMap();

    void showDieMessage();

    void incScore(const int& Add);

    int getScore();

    void doShot();

    virtual void update(std::shared_ptr<GameObject>& refObj);

    virtual void collide(std::shared_ptr<GameObject>);
    virtual void collide(std::shared_ptr<Hero>);
    virtual void collide(std::shared_ptr<Zombie>);
    virtual void collide(std::shared_ptr<Princess>);
    virtual void collide(std::shared_ptr<Projectile>);
    virtual void collide(std::shared_ptr<Dragon>);
    virtual void collide(std::shared_ptr<Trap>);
    virtual void collide(std::shared_ptr<Wall>);
    virtual void collide(std::shared_ptr<Medkit>);

    void doCollide(std::shared_ptr<Hero>);
    void doCollide(std::shared_ptr<Zombie>);
    void doCollide(std::shared_ptr<Princess>);
    void doCollide(std::shared_ptr<Projectile>);
    void doCollide(std::shared_ptr<Dragon>);
    void doCollide(std::shared_ptr<Trap>);
    void doCollide(std::shared_ptr<Wall>);
    void doCollide(std::shared_ptr<Medkit>);

private:
    std::shared_ptr<Projectile> shot();

    int score = 0;
    bool doShot_ = false;
    int lastShotTime;
};
}  // namespace GameObject
