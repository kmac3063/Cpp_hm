#pragma once

#include <memory>

#include "Subject.h"
#include "Character.h"

bool GameObject::Subject::isAlive() {
    return exist;
}


char GameObject::Wall::getSymbOnMap() {
    return '#';
}

void GameObject::Wall::update(std::shared_ptr<GameObject>& g) {}

void GameObject::Wall::collide(std::shared_ptr<GameObject> obj) {
    obj->collide(std::shared_ptr<Wall>(this));
}
void GameObject::Wall::collide(std::shared_ptr<Hero> h) {
    doCollide(h);
    h->doCollide(std::shared_ptr<Wall>(this));
}
void GameObject::Wall::collide(std::shared_ptr<Zombie> z) {
    doCollide(z);
    z->doCollide(std::shared_ptr<Wall>(this));
}
void GameObject::Wall::collide(std::shared_ptr<Princess> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Wall>(this));
}
void GameObject::Wall::collide(std::shared_ptr<Projectile> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Wall>(this));
}
void GameObject::Wall::collide(std::shared_ptr<Dragon> d) {
    doCollide(d);
    d->doCollide(std::shared_ptr<Wall>(this));
}
void GameObject::Wall::collide(std::shared_ptr<Trap> t) {
    doCollide(t);
    t->doCollide(std::shared_ptr<Wall>(this));
}
void GameObject::Wall::collide(std::shared_ptr<Wall> w) {
    doCollide(w);
    w->doCollide(std::shared_ptr<Wall>(this));
}
void GameObject::Wall::collide(std::shared_ptr<Medkit> m) {
    doCollide(m);
    m->doCollide(std::shared_ptr<Wall>(this));
}

void GameObject::Wall::doCollide(std::shared_ptr<Hero> h) {}
void GameObject::Wall::doCollide(std::shared_ptr<Zombie> z) {}
void GameObject::Wall::doCollide(std::shared_ptr<Princess> p) {}
void GameObject::Wall::doCollide(std::shared_ptr<Projectile> p) {}
void GameObject::Wall::doCollide(std::shared_ptr<Dragon> d) {}
void GameObject::Wall::doCollide(std::shared_ptr<Trap> t) {}
void GameObject::Wall::doCollide(std::shared_ptr<Wall> w) {}
void GameObject::Wall::doCollide(std::shared_ptr<Medkit> m) {}


GameObject::Medkit::Medkit() : healPoint(HP_TABLE[getSymbOnMap()]) {}

char GameObject::Medkit::getSymbOnMap() {
    return '+';
}

void GameObject::Medkit::update(std::shared_ptr<GameObject>& g) {}

int GameObject::Medkit::getHP() { return healPoint; }

void GameObject::Medkit::collide(std::shared_ptr<GameObject> obj) {
    obj->collide(std::shared_ptr<Medkit>(this));
}
void GameObject::Medkit::collide(std::shared_ptr<Hero> h) {
    doCollide(h);
    h->doCollide(std::shared_ptr<Medkit>(this));
}
void GameObject::Medkit::collide(std::shared_ptr<Zombie> z) {
    doCollide(z);
    z->doCollide(std::shared_ptr<Medkit>(this));
}
void GameObject::Medkit::collide(std::shared_ptr<Princess> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Medkit>(this));
}
void GameObject::Medkit::collide(std::shared_ptr<Projectile> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Medkit>(this));
}
void GameObject::Medkit::collide(std::shared_ptr<Dragon> d) {
    doCollide(d);
    d->doCollide(std::shared_ptr<Medkit>(this));
}
void GameObject::Medkit::collide(std::shared_ptr<Trap> t) {
    doCollide(t);
    t->doCollide(std::shared_ptr<Medkit>(this));
}
void GameObject::Medkit::collide(std::shared_ptr<Wall> w) {
    doCollide(w);
    w->doCollide(std::shared_ptr<Medkit>(this));
}
void GameObject::Medkit::collide(std::shared_ptr<Medkit> m) {
    doCollide(m);
    m->doCollide(std::shared_ptr<Medkit>(this));
}

void GameObject::Medkit::doCollide(std::shared_ptr<Hero> h) {
    h->heal(healPoint);
    exist = false;
}
void GameObject::Medkit::doCollide(std::shared_ptr<Zombie> z) {}
void GameObject::Medkit::doCollide(std::shared_ptr<Princess> p) {
    p->heal(healPoint);
    exist = false;
}
void GameObject::Medkit::doCollide(std::shared_ptr<Projectile> p) {
    exist = false;
}
void GameObject::Medkit::doCollide(std::shared_ptr<Dragon> d) {}
void GameObject::Medkit::doCollide(std::shared_ptr<Trap> t) {}
void GameObject::Medkit::doCollide(std::shared_ptr<Wall> w) {}
void GameObject::Medkit::doCollide(std::shared_ptr<Medkit> m) {}