#pragma once

namespace Factory {
class Factory {
public:
    virtual GameObject::GameObject* CreateGameObject(const int&, const int&) = 0;
};

class FactoryHero : public Factory {
public:
    virtual GameObject::GameObject* CreateGameObject(const int& y, const int& x) {
        auto obj = new GameObject::Hero();
        obj->setPos(y, x);
        return obj;
    }
};

class FactoryPrincess : public Factory {
public:
    virtual GameObject::GameObject* CreateGameObject(const int& y, const int& x) {
        auto obj = new GameObject::Princess();
        obj->setPos(y, x);
        return obj;
    }
};

class FactoryZombie : public Factory {
public:
    virtual GameObject::GameObject* CreateGameObject(const int& y, const int& x) {
        auto obj = new GameObject::Zombie();
        obj->setPos(y, x);
        return obj;
    }
};

class FactoryDragon : public Factory {
public:
    virtual GameObject::GameObject* CreateGameObject(const int& y, const int& x) {
        auto obj = new GameObject::Dragon();
        obj->setPos(y, x);
        return obj;
    }
};

class FactoryMedkit : public Factory {
public:
    virtual GameObject::GameObject* CreateGameObject(const int& y, const int& x) {
        auto obj = new GameObject::Medkit();
        obj->setPos(y, x);
        return obj;
    }
};

class FactoryWall : public Factory {
public:
    virtual GameObject::GameObject* CreateGameObject(const int& y, const int& x) {
        auto obj = new GameObject::Wall();
        obj->setPos(y, x);
        return obj;
    }
};

class FactoryTrap : public Factory {
public:
    virtual GameObject::GameObject* CreateGameObject(const int& y, const int& x) {
        auto obj = new GameObject::Trap();
        obj->setPos(y, x);
        return obj;
    }
};
}