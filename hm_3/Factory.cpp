#pragma once

#include "Factory.h"

#include "GameObject/Character.h"
#include "GameObject/Subject.h"

GameObject::GameObject* Factory::FactoryHero::CreateGameObject(const int& y, const int& x) {
    auto obj = new GameObject::Hero();
    obj->setPos(y, x);
    
    return obj;
}

GameObject::GameObject* Factory::FactoryPrincess::CreateGameObject(const int& y, const int& x) {
    auto obj = new GameObject::Princess();
    obj->setPos(y, x);
  
    return obj;
}

GameObject::GameObject* Factory::FactoryZombie::CreateGameObject(const int& y, const int& x) {
    auto obj = new GameObject::Zombie();
    obj->setPos(y, x);

    return obj;
}

GameObject::GameObject* Factory::FactoryDragon::CreateGameObject(const int& y, const int& x) {
    auto obj = new GameObject::Dragon();
    obj->setPos(y, x);
    
    return obj;
}

GameObject::GameObject* Factory::FactoryMedkit::CreateGameObject(const int& y, const int& x) {
    auto obj = new GameObject::Medkit();
    obj->setPos(y, x);
    
    return obj;
}

GameObject::GameObject* Factory::FactoryWall::CreateGameObject(const int& y, const int& x) {
    auto obj = new GameObject::Wall();
    obj->setPos(y, x);
    
    return obj;
}

GameObject::GameObject* Factory::FactoryTrap::CreateGameObject(const int& y, const int& x) {
    auto obj = new GameObject::Trap();
    obj->setPos(y, x);

    return obj;
}