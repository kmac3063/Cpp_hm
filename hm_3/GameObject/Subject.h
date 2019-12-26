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
    virtual void update(std::shared_ptr<GameObject>& refObj);
    
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

class Medkit : public Subject {
public:
    Medkit();
    virtual void update(std::shared_ptr<GameObject>& refObj);

    virtual char getSymbOnMap();

    int getHP();

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
    int healPoint;
};
}  // namespace GameObject