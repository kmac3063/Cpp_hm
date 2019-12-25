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
        int64_t timeNowMs = clock();
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
    Projectile* shot() {
        auto timeNow = clock();
        if (timeNow < lastShotTime + HERO_RELOAD_TIME)
            return nullptr;

        lastShotTime = timeNow;

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
    int lastShotTime;
    std::pair<int, int> lastDir;
};

Hero* hero;

class Dragon : public Enemy{
public:
    Dragon() : Enemy(HP_TABLE[getSymbOnMap()],
        DMG_TABLE[getSymbOnMap()],
        SLEEPTIME_TABLE[getSymbOnMap()]) {}

    
    virtual char getSymbOnMap() {
        return 'D';
    }

    virtual void update(GameObject*& refObj) {
        auto dy = hero->getCoordY() - y;
        if (dy != 0) dy /= abs(dy);

        auto dx = hero->getCoordX() - x;
        if (dx != 0) dx /= abs(dx);

        if (dy == 0) {
            dir(0, dx);
            refObj = shot(0, dx);
        }
        else if (dx == 0) {
            dir(dy, 0);
            refObj = shot(dy, 0);
        }
        else if (rand() % 2) {
            dir(dy, 0);
        }
        else {
            dir(0, dx);
        }
        
        move();
    }
private:
    int64_t lastShotTime = 0;
    Projectile* shot(const int& dy, const int& dx) {
        auto timeNow = clock();
        if (timeNow < lastShotTime + DRAGON_RELOAD_TIME)
            return nullptr;

        lastShotTime = timeNow;

        Projectile* p = new Projectile();
        p->setPos(y + dy, x + dx);
        p->dir(dy, dx);

        return p;
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

    virtual void update(GameObject*& refObj) {
        auto dy = hero->getCoordY() - y;
        if (dy != 0) dy /= abs(dy);
        
        auto dx = hero->getCoordX() - x;
        if (dx != 0) dx /= abs(dx);

        int rnd = rand() % 100;
        if (rnd < 15)
            dir(dy, dx);
        else if (rnd < 40) 
            dir(0, dx);
        else if (rnd < 66) // 66% что шаг будет в мою сторону
            dir(dy, 0);
        else if (rnd < 84) 
            dir(-dy, 0);
        else
            dir(0, -dx);

        move();
    }

    
    void collide(Hero* hero);
    void collide(Zombie* zombie);
    void collide(Dragon* dragon);
    void collide(Princess* princess);
    void collide(Wall* wall);
    void collide(Trap* trap);
    void collide(Medkit* medkit);

    void doCollide(Hero* hero);
    void doCollide(Zombie* zombie);
    void doCollide(Dragon* dragon);
    void doCollide(Princess* princess);
    void doCollide(Wall* wall);
    void doCollide(Trap* trap);
    void doCollide(Medkit* medkit);
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


}  // namespace GameObject
