#pragma once

#include "GameObject.h"

namespace GameObject {
class Character : public GameObject {
public:
    void die();
    void move(int dy, int dx) {
        y += dy;
        x += dx;
    }
    
    void setHP(int hp_) {
        hp = hp_;
    }

    void damage(int damage) {
        hp -= damage;
        if (hp <= 0)
            die();
    }

    void heal(int heal) {
        hp = min(HP_TABLE['H'], hp + heal);
    }
protected:
    int hp;
};

class Hero : public Character {
public:
    virtual char getSymbOnMap() {
        return 'H';
    }

    void die() {
        Visual::showMessage("YOU DIE");
    }
};


class Friendly : public Character {

};

class Princess : public Friendly {
    virtual char getSymbOnMap() {
        return 'P';
    }
};


class Enemy : public Character {

};

class Zombie : public Enemy {
    virtual char getSymbOnMap() {
        return 'Z';
    }
};

class Dragon : public Enemy {
    virtual char getSymbOnMap() {
        return 'D';
    }
};

}  // namespace GameObject