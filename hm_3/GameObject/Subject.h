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
public:
    virtual void update(GameObject*& refObj);
    
    virtual char getSymbOnMap();

    virtual void collide(GameObject*);
    virtual void collide(Hero*);
    virtual void collide(Zombie*);
    virtual void collide(Princess*);
    virtual void collide(Projectile*);
    virtual void collide(Dragon*);
    virtual void collide(Trap*);
    virtual void collide(Wall*);
    virtual void collide(Medkit*);

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
public:
    Medkit();
    virtual void update(GameObject*& refObj);

    virtual char getSymbOnMap();

    int getHP();

    virtual void collide(GameObject*);
    virtual void collide(Hero*);
    virtual void collide(Zombie*);
    virtual void collide(Princess*);
    virtual void collide(Projectile*);
    virtual void collide(Dragon*);
    virtual void collide(Trap*);
    virtual void collide(Wall*);
    virtual void collide(Medkit*);

    void doCollide(Hero*);
    void doCollide(Zombie*);
    void doCollide(Princess*);
    void doCollide(Projectile*);
    void doCollide(Dragon*);
    void doCollide(Trap*);
    void doCollide(Wall*);
    void doCollide(Medkit*);
private:
    int healPoint;
};
}  // namespace GameObject