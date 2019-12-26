#pragma once

#include <memory>

#include "Factory.h"

#include "GameObject/Character.h"
#include "GameObject/Subject.h"

typedef typename std::shared_ptr<GameObject::GameObject> sPtrGameObject;

sPtrGameObject Factory::FactoryHero::CreateGameObject(const int& y, const int& x) {
    auto obj = sPtrGameObject(new GameObject::Hero());
    obj->setPos(y, x);
    
    return obj;
}

sPtrGameObject Factory::FactoryPrincess::CreateGameObject(const int& y, const int& x) {
    auto obj = sPtrGameObject(new GameObject::Princess());
    obj->setPos(y, x);
  
    return obj;
}

sPtrGameObject Factory::FactoryZombie::CreateGameObject(const int& y, const int& x) {
    auto obj = sPtrGameObject(new GameObject::Zombie());
    obj->setPos(y, x);

    return obj;
}

sPtrGameObject Factory::FactoryDragon::CreateGameObject(const int& y, const int& x) {
    auto obj = sPtrGameObject(new GameObject::Dragon());
    obj->setPos(y, x);
    
    return obj;
}

sPtrGameObject Factory::FactoryMedkit::CreateGameObject(const int& y, const int& x) {
    auto obj = sPtrGameObject(new GameObject::Medkit());
    obj->setPos(y, x);
    
    return obj;
}

sPtrGameObject Factory::FactoryWall::CreateGameObject(const int& y, const int& x) {
    auto obj = sPtrGameObject(new GameObject::Wall());
    obj->setPos(y, x);
    
    return obj;
}

sPtrGameObject Factory::FactoryTrap::CreateGameObject(const int& y, const int& x) {
    auto obj = sPtrGameObject(new GameObject::Trap());
    obj->setPos(y, x);

    return obj;
}