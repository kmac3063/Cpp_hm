#pragma once

#include <memory>

#include "GameObject/GameObject.h"

typedef typename std::shared_ptr<GameObject::GameObject> sPtrGameObject;

namespace Factory {
class Factory {
public:
    virtual sPtrGameObject CreateGameObject(const int&, const int&) = 0;
};

class FactoryHero : public Factory {
public:
    virtual sPtrGameObject CreateGameObject(const int& y, const int& x);
};

class FactoryPrincess : public Factory {
public:
    virtual sPtrGameObject CreateGameObject(const int& y, const int& x);
};

class FactoryZombie : public Factory {
public:
    virtual sPtrGameObject CreateGameObject(const int& y, const int& x);
};

class FactoryDragon : public Factory {
public:
    virtual sPtrGameObject CreateGameObject(const int& y, const int& x);
};

class FactoryMedkit : public Factory {
public:
    virtual sPtrGameObject CreateGameObject(const int& y, const int& x);
};

class FactoryWall : public Factory {
public:
    virtual sPtrGameObject CreateGameObject(const int& y, const int& x);
};

class FactoryTrap : public Factory {
public:
    virtual sPtrGameObject CreateGameObject(const int& y, const int& x);
};
}  // namespace Factory