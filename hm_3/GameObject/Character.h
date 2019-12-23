#pragma once

#include "GameObject.h"

namespace GameObject {
class Character : public GameObject {
public:
    Character(const int& HP, const int& Dmg, const int64_t& SleepTimeMs) : 
        hp(HP), dmg(Dmg), sleepTimeMs(SleepTimeMs)  {}

    virtual void dir(const int& dy_, const int& dx_) {
        dy = dy_;
        dx = dx_;
    }

    virtual void move() {
        uint64_t timeNowMs = clock();
        if (timeNowMs < lastUseMs + sleepTimeMs) {
            return;
        }
        y += dy;
        x += dx;

        dy = dx = 0;
        lastUseMs = clock();
    }
    
    void setHP(int hp_) {
        hp = hp_;
    }

    void damage(int damage) {
        hp -= damage;
    }

    bool live() {
        return hp > 0;
    }

    void heal(int heal) {
        hp = min(HP_TABLE['H'], hp + heal);
    }
protected:
    const int64_t sleepTimeMs;
    int64_t lastUseMs = -sleepTimeMs;

    int hp, dmg;
    int dx = 0, dy = 0;
};

class Hero : public Character {
public:
    Hero() : Character(HP_TABLE[getSymbOnMap()], 
        DMG_TABLE[getSymbOnMap()], 
        SPEEPTIME_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'H';
    }

    virtual void move() {
        if (dy != 0 || dx != 0)
            lastDir = { dy, dx };
        Character::move();
    }

    void showDieMessage() {
        Visual::showMessage("YOU DIE");
    }

    auto getLastDir() {
        return lastDir;
    }
private:
    std::pair<int, int> lastDir;
};


class Friendly : public Character {
public:
    Friendly(const int& HP, const int& Dmg, const int64_t& SleepTimeMs)
        : Character(HP, Dmg, SleepTimeMs) {}
};

class Princess : public Friendly {
public:
    Princess() : Friendly(HP_TABLE[getSymbOnMap()],
        DMG_TABLE[getSymbOnMap()],
        SPEEPTIME_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'P';
    }
};


class Enemy : public Character {
public:
    Enemy(const int& HP, const int& Dmg, const int64_t& SleepTimeMs) 
        : Character(HP, Dmg, SleepTimeMs) {}
};

class Zombie : public Enemy {
public:
    Zombie() : Enemy(HP_TABLE[getSymbOnMap()],
        DMG_TABLE[getSymbOnMap()],
        SPEEPTIME_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'Z';
    }
};

class Dragon : public Enemy {
public:
    Dragon() : Enemy(HP_TABLE[getSymbOnMap()],
        DMG_TABLE[getSymbOnMap()],
        SPEEPTIME_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'D';
    }
};

class Projectile : public Enemy {
public:
    Projectile() : Enemy(HP_TABLE[getSymbOnMap()],
        DMG_TABLE[getSymbOnMap()],
        SPEEPTIME_TABLE[getSymbOnMap()]) {}

    virtual void dir(const int& dy_, const int& dx_) {
        Enemy::dir(dy_, dx_);
        if (dy == 0 && dx == 0)
            dx = 1;
    }

    virtual char getSymbOnMap() {
        return '*';
    }
    
    virtual void move() {
        uint64_t timeNowMs = clock();
        if (timeNowMs < lastUseMs + sleepTimeMs) {
            return;
        }
        y += dy;
        x += dx;

        lastUseMs = clock();
    }
};

}  // namespace GameObject
