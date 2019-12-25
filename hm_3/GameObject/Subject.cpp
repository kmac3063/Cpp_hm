#pragma once

#include "Subject.h"

bool GameObject::Subject::isAlive() {
    return exist;
}


char GameObject::Wall::getSymbOnMap() {
    return '#';
}

void GameObject::Wall::update(GameObject*& g) {}

void GameObject::Wall::collide(GameObject* obj) {}
void GameObject::Wall::collide(Hero* h) {}
void GameObject::Wall::collide(Zombie* z) {}
void GameObject::Wall::collide(Princess* p) {}
void GameObject::Wall::collide(Projectile* p) {}
void GameObject::Wall::collide(Dragon* d) {}
void GameObject::Wall::collide(Trap* t) {}
void GameObject::Wall::collide(Wall* w) {}
void GameObject::Wall::collide(Medkit* m) {}

void GameObject::Wall::doCollide(Hero* h) {}
void GameObject::Wall::doCollide(Zombie* z) {}
void GameObject::Wall::doCollide(Princess* p) {}
void GameObject::Wall::doCollide(Projectile* p) {}
void GameObject::Wall::doCollide(Dragon* d) {}
void GameObject::Wall::doCollide(Trap* t) {}
void GameObject::Wall::doCollide(Wall* w) {}
void GameObject::Wall::doCollide(Medkit* m) {}


char GameObject::Medkit::getSymbOnMap() {
    return '+';
}

void GameObject::Medkit::update(GameObject*& g) {}

void GameObject::Medkit::collide(GameObject* obj) {}
void GameObject::Medkit::collide(Hero* h) {}
void GameObject::Medkit::collide(Zombie* z) {}
void GameObject::Medkit::collide(Princess* p) {}
void GameObject::Medkit::collide(Projectile* p) {}
void GameObject::Medkit::collide(Dragon* d) {}
void GameObject::Medkit::collide(Trap* t) {}
void GameObject::Medkit::collide(Wall* w) {}
void GameObject::Medkit::collide(Medkit* m) {}

void GameObject::Medkit::doCollide(Hero* h) {}
void GameObject::Medkit::doCollide(Zombie* z) {}
void GameObject::Medkit::doCollide(Princess* p) {}
void GameObject::Medkit::doCollide(Projectile* p) {}
void GameObject::Medkit::doCollide(Dragon* d) {}
void GameObject::Medkit::doCollide(Trap* t) {}
void GameObject::Medkit::doCollide(Wall* w) {}
void GameObject::Medkit::doCollide(Medkit* m) {}