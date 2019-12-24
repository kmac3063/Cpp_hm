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

    
    void setHP(int hp_) {
        hp = hp_;
    }

    int getHP() {
        return hp;
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

    virtual void update(GameObject*& refObj) {
        move();
    }
protected:
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
    const int64_t sleepTimeMs;
    int64_t lastUseMs = -sleepTimeMs;

    int hp, dmg;
    int dx = 0, dy = 0;
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
        SLEEPTIME_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'P';
    }
};


class Enemy : public Character {
public:
    Enemy(const int& HP, const int& Dmg, const int64_t& SleepTimeMs) 
        : Character(HP, Dmg, SleepTimeMs) {}
};

class Projectile : public Enemy {
public:
    Projectile() : Enemy(HP_TABLE[getSymbOnMap()],
        DMG_TABLE[getSymbOnMap()],
        SLEEPTIME_TABLE[getSymbOnMap()]) {}

    virtual void dir(const int& dy_, const int& dx_) {
        Enemy::dir(dy_, dx_);
        if (dy == 0 && dx == 0)
            dx = 1;
    }

    virtual char getSymbOnMap() {
        return '*';
    }
private:
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

class Dragon : public Enemy{
public:
    Dragon() : Enemy(HP_TABLE[getSymbOnMap()],
        DMG_TABLE[getSymbOnMap()],
        SLEEPTIME_TABLE[getSymbOnMap()]) {}

    
    virtual char getSymbOnMap() {
        return 'D';
    }
};

class Zombie : public Enemy {
public:
    Zombie() : Enemy(HP_TABLE[getSymbOnMap()],
        DMG_TABLE[getSymbOnMap()],
        SLEEPTIME_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'Z';
    }
};

class Trap : public Enemy {
public:
    Trap() : Enemy(HP_TABLE[getSymbOnMap()],
        DMG_TABLE[getSymbOnMap()],
        SLEEPTIME_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'T';
    }
};


class Hero : public Character {
public:
    Hero() : Character(HP_TABLE[getSymbOnMap()], 
        DMG_TABLE[getSymbOnMap()], 
        SLEEPTIME_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'H';
    }

    void showDieMessage() {
        Visual::showMessage("YOU DIE");
    }

    void incScore(const int& Add) {
        score += Add;
    }

    int getScore() {
        return score;
    }

    void doShot() {
        doShot_ = true;
    }

    virtual void update(GameObject*& refObj) {
        move();
        if (doShot_) {
            refObj = shot();
            doShot_ = false;
        }
    }
private:
    virtual Projectile* shot() {
        Projectile* p = new Projectile();

        p->setPos(y + lastDir.first, x + lastDir.second);
        p->dir(lastDir.first, lastDir.second);
        
        return p;
    }
    
    virtual void move() {
        if (dy != 0 || dx != 0)
            lastDir = { dy, dx };
        Character::move();
    }

    int score = 0;
    bool doShot_ = false;
    std::pair<int, int> lastDir;
};







}  // namespace GameObject
