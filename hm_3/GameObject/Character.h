#pragma once

#include "GameObject.h"

namespace GameObject {
class Character : public GameObject {
public:
    Character(const int& HP) : hp(HP) {}

    virtual void dir(const int& dy_, const int& dx_) {
        dy = dy_;
        dx = dx_;
    }

    virtual void move() {
        if (dx == 0 && dy == 0) return;
        y += dy;
        x += dx;

        dy = dx = 0;
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
    int hp;
    int dx = 0, dy = 0;
};

class Hero : public Character {
public:
    Hero() : Character(HP_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'H';
    }

    virtual void move() {
        if (dx == 0 && dy == 0) return;
        y += dy;
        x += dx;
        
        lastDir = { dy, dx };

        dy = dx = 0;
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
    Friendly(int hp) : Character(hp) {}
};

class Princess : public Friendly {
public:
    Princess() : Friendly(HP_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'P';
    }
};


class Enemy : public Character {
public:
    Enemy(int hp) : Character(hp) {}
};

class Zombie : public Enemy {
public:
    Zombie() : Enemy(HP_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'Z';
    }
};

class Dragon : public Enemy {
public:
    Dragon() : Enemy(HP_TABLE[getSymbOnMap()]) {}

    virtual char getSymbOnMap() {
        return 'D';
    }
};

class Projectile : public Enemy {
public:
    Projectile() : Enemy(HP_TABLE[getSymbOnMap()]) {}

    virtual void dir(const int& dy_, const int& dx_) {
        dx = dx_;
        dy = dy_;

        if (dy_ == 0 && dx_ == 0)
            dx = 1;
    }

    virtual char getSymbOnMap() {
        return '*';
    }
    
    virtual void move() {
        y += dy;
        x += dx;
    }
};

}  // namespace GameObject
