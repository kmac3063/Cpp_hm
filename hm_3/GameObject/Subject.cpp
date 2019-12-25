#pragma once

#include "Subject.h"
#include "Character.h"

bool GameObject::Subject::isAlive() {
    return exist;
}


char GameObject::Wall::getSymbOnMap() {
    return '#';
}

void GameObject::Wall::update(GameObject*& g) {}

void GameObject::Wall::collide(GameObject* obj) {
    obj->collide(this);
}
void GameObject::Wall::collide(Hero* h) {
    doCollide(h);
    h->doCollide(this);
}
void GameObject::Wall::collide(Zombie* z) {
    doCollide(z);
    z->doCollide(this);
}
void GameObject::Wall::collide(Princess* p) {
    doCollide(p);
    p->doCollide(this);
}
void GameObject::Wall::collide(Projectile* p) {
    doCollide(p);
    p->doCollide(this);
}
void GameObject::Wall::collide(Dragon* d) {
    doCollide(d);
    d->doCollide(this);
}
void GameObject::Wall::collide(Trap* t) {
    doCollide(t);
    t->doCollide(this);
}
void GameObject::Wall::collide(Wall* w) {
    doCollide(w);
    w->doCollide(this);
}
void GameObject::Wall::collide(Medkit* m) {
    doCollide(m);
    m->doCollide(this);
}

void GameObject::Wall::doCollide(Hero* h) {}
void GameObject::Wall::doCollide(Zombie* z) {}
void GameObject::Wall::doCollide(Princess* p) {}
void GameObject::Wall::doCollide(Projectile* p) {}
void GameObject::Wall::doCollide(Dragon* d) {}
void GameObject::Wall::doCollide(Trap* t) {}
void GameObject::Wall::doCollide(Wall* w) {}
void GameObject::Wall::doCollide(Medkit* m) {}


GameObject::Medkit::Medkit() : healPoint(HP_TABLE[getSymbOnMap()]) {}

char GameObject::Medkit::getSymbOnMap() {
    return '+';
}

void GameObject::Medkit::update(GameObject*& g) {}

int GameObject::Medkit::getHP() { return healPoint; }

void GameObject::Medkit::collide(GameObject* obj) {
    obj->collide(this);
}
void GameObject::Medkit::collide(Hero* h) {
    doCollide(h);
    h->doCollide(this);
}
void GameObject::Medkit::collide(Zombie* z) {
    doCollide(z);
    z->doCollide(this);
}
void GameObject::Medkit::collide(Princess* p) {
    doCollide(p);
    p->doCollide(this);
}
void GameObject::Medkit::collide(Projectile* p) {
    doCollide(p);
    p->doCollide(this);
}
void GameObject::Medkit::collide(Dragon* d) {
    doCollide(d);
    d->doCollide(this);
}
void GameObject::Medkit::collide(Trap* t) {
    doCollide(t);
    t->doCollide(this);
}
void GameObject::Medkit::collide(Wall* w) {
    doCollide(w);
    w->doCollide(this);
}
void GameObject::Medkit::collide(Medkit* m) {
    doCollide(m);
    m->doCollide(this);
}

void GameObject::Medkit::doCollide(Hero* h) {
    h->heal(healPoint);
    exist = false;
}
void GameObject::Medkit::doCollide(Zombie* z) {}
void GameObject::Medkit::doCollide(Princess* p) {
    p->heal(healPoint);
    exist = false;
}
void GameObject::Medkit::doCollide(Projectile* p) {
    exist = false;
}
void GameObject::Medkit::doCollide(Dragon* d) {}
void GameObject::Medkit::doCollide(Trap* t) {}
void GameObject::Medkit::doCollide(Wall* w) {}
void GameObject::Medkit::doCollide(Medkit* m) {}