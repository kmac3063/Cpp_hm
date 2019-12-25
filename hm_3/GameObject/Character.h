#pragma once

#include "GameObject.h"

namespace GameObject {
class Character : public GameObject {
public:
    Character(const int& HP, const int& Dmg, const int64_t& SleepTimeMs);
    virtual void dir(const int& dy_, const int& dx_);
    
    void setHP(const int& hp_);
    int getHP();

    void damage(const int& damage);
    void heal(const int& heal);
    virtual bool isAlive();

    virtual void update(GameObject*& refObj);

    void getLastDir(int& dy, int& dx);

protected:
    virtual void move();

    const int64_t sleepTimeMs;
    int64_t lastUseMs = -sleepTimeMs;
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

    void collide(GameObject*);
    void collide(Hero*);
    void collide(Zombie*);
    void collide(Princess*);
    void collide(Projectile*);
    void collide(Dragon*);
    void collide(Trap*);
    void collide(Wall*);
    void collide(Medkit*);

    void doCollide(Hero*);
    void doCollide(Zombie*);
    void doCollide(Princess*);
    void doCollide(Projectile*);
    void doCollide(Dragon*);
    void doCollide(Trap*);
    void doCollide(Wall*);
    void doCollide(Medkit*);

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

    void collide(GameObject*);
    void collide(Hero*);
    void collide(Zombie*);
    void collide(Princess*);
    void collide(Projectile*);
    void collide(Dragon*);
    void collide(Trap*);
    void collide(Wall*);
    void collide(Medkit*);

    void doCollide(Hero*);
    void doCollide(Zombie*);
    void doCollide(Princess*);
    void doCollide(Projectile*);
    void doCollide(Dragon*);
    void doCollide(Trap*);
    void doCollide(Wall*);
    void doCollide(Medkit*);

private:
    virtual void move();
};

class Dragon : public Enemy{
public:
    Dragon();
    
    virtual char getSymbOnMap();

    virtual void update(GameObject*& refObj);

    void collide(GameObject*);
    void collide(Hero*);
    void collide(Zombie*);
    void collide(Princess*);
    void collide(Projectile*);
    void collide(Dragon*);
    void collide(Trap*);
    void collide(Wall*);
    void collide(Medkit*);

    void doCollide(Hero*);
    void doCollide(Zombie*);
    void doCollide(Princess*);
    void doCollide(Projectile*);
    void doCollide(Dragon*);
    void doCollide(Trap*);
    void doCollide(Wall*);
    void doCollide(Medkit*);

private:
    int64_t lastShotTime = 0;
    Projectile* shot(const int& dy, const int& dx);
};

class Zombie : public Enemy {
public:
    Zombie();

    virtual char getSymbOnMap();

    virtual void update(GameObject*& refObj);

    void collide(GameObject*);
    void collide(Hero*);
    void collide(Zombie*);
    void collide(Princess*);
    void collide(Projectile*);
    void collide(Dragon*);
    void collide(Trap*);
    void collide(Wall*);
    void collide(Medkit*);

    void doCollide(Hero*);
    void doCollide(Zombie*);
    void doCollide(Princess*);
    void doCollide(Projectile*);
    void doCollide(Dragon*);
    void doCollide(Trap*);
    void doCollide(Wall*);
    void doCollide(Medkit*);
};

class Trap : public Enemy {
public:
    Trap();

    void collide(GameObject*);
    void collide(Hero*);
    void collide(Zombie*);
    void collide(Princess*);
    void collide(Projectile*);
    void collide(Dragon*);
    void collide(Trap*);
    void collide(Wall*);
    void collide(Medkit*);
    
    void doCollide(Hero*);
    void doCollide(Zombie*);
    void doCollide(Princess*);
    void doCollide(Projectile*);
    void doCollide(Dragon*);
    void doCollide(Trap*);
    void doCollide(Wall*);
    void doCollide(Medkit*);

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

    virtual void update(GameObject*& refObj);

    void collide(GameObject*);
    void collide(Hero*);
    void collide(Zombie*);
    void collide(Princess*);
    void collide(Projectile*);
    void collide(Dragon*);
    void collide(Trap*);
    void collide(Wall*);
    void collide(Medkit*);

    void doCollide(Hero*);
    void doCollide(Zombie*);
    void doCollide(Princess*);
    void doCollide(Projectile*);
    void doCollide(Dragon*);
    void doCollide(Trap*);
    void doCollide(Wall*);
    void doCollide(Medkit*);

private:
    Projectile* shot();

    int score = 0;
    bool doShot_ = false;
    int lastShotTime;
};
}  // namespace GameObject
