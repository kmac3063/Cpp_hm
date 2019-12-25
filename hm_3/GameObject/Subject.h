#pragma once

#include "GameObject.h"

namespace GameObject {
class Subject : public GameObject {
public:
    virtual bool isAlive();

protected:
    bool exist = true;
};

class Wall : public Subject {
    virtual void update(GameObject*& refObj);
    
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

class Medkit : public Subject {
    virtual void update(GameObject*& refObj);

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
}  // namespace GameObject