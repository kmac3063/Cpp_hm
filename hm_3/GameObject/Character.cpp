#pragma once
#include <algorithm>
#include <cmath>
#include <thread>

#include "../constants.h"
#include "../Visual.h"
#include "Character.h"

GameObject::Character::Character(const int& HP, const int& Dmg, const int64_t& SleepTimeMs) :
    hp(HP), dmg(Dmg), sleepTimeMs(SleepTimeMs) {}

void GameObject::Character::dir(const int& dy_, const int& dx_) {
    if (dy != 0 || dx != 0)
        lastDir = { dy, dx };
    dy = dy_;
    dx = dx_;
}

void GameObject::Character::setHP(const int& hp_) {
    hp = hp_;
}

int GameObject::Character::getHP() {
    return hp;
}

void GameObject::Character::damage(const int& damage) {
    hp -= damage;
}

bool GameObject::Character::isAlive() {
    return hp > 0;
}

void GameObject::Character::heal(const int& heal) {
    hp = std::min(HP_TABLE['H'], hp + heal);
}

void GameObject::Character::update(GameObject*& refObj) {
    move();
}

void GameObject::Character::move() {
    int64_t timeNowMs = clock();
    if (timeNowMs < lastUseMs + sleepTimeMs) {
        return;
    }
    y += dy;
    x += dx;

    dy = dx = 0;
    lastUseMs = clock();
}

void GameObject::Character::getLastDir(int& dy, int& dx) {
    dy = lastDir.first;
    dx = lastDir.second;
}


GameObject::Friendly::Friendly(const int& HP, const int& Dmg, const int64_t& SleepTimeMs)
    : Character(HP, Dmg, SleepTimeMs) {}

GameObject::Princess::Princess() : Friendly(HP_TABLE[getSymbOnMap()],
    DMG_TABLE[getSymbOnMap()],
    SLEEPTIME_TABLE[getSymbOnMap()]) {}

char GameObject::Princess::getSymbOnMap() {
    return 'P';
}

void GameObject::Princess::collide(GameObject* obj) {}
void GameObject::Princess::collide(Hero* h) {}
void GameObject::Princess::collide(Zombie* z) {}
void GameObject::Princess::collide(Princess* p) {}
void GameObject::Princess::collide(Projectile* p) {}
void GameObject::Princess::collide(Dragon* d) {}
void GameObject::Princess::collide(Trap* t) {}
void GameObject::Princess::collide(Wall* w) {}
void GameObject::Princess::collide(Medkit* m) {}

void GameObject::Princess::doCollide(Hero* h) {}
void GameObject::Princess::doCollide(Zombie* z) {}
void GameObject::Princess::doCollide(Princess* p) {}
void GameObject::Princess::doCollide(Projectile* p) {}
void GameObject::Princess::doCollide(Dragon* d) {}
void GameObject::Princess::doCollide(Trap* t) {}
void GameObject::Princess::doCollide(Wall* w) {}
void GameObject::Princess::doCollide(Medkit* m) {}

GameObject::Enemy::Enemy(const int& HP, const int& Dmg, const int64_t& SleepTimeMs)
    : Character(HP, Dmg, SleepTimeMs) {}

GameObject::Projectile::Projectile() : Enemy(HP_TABLE[getSymbOnMap()],
    DMG_TABLE[getSymbOnMap()],
    SLEEPTIME_TABLE[getSymbOnMap()]) {}

void GameObject::Projectile::dir(const int& dy_, const int& dx_) {
    if (dy_ == 0 && dx_ == 0)
        Enemy::dir(0, 1);
    else
        Enemy::dir(dy_, dx_);
}

char GameObject::Projectile::getSymbOnMap() {
    return '*';
}

void GameObject::Projectile::move() {
    uint64_t timeNowMs = clock();
    if (timeNowMs < lastUseMs + sleepTimeMs) {
        return;
    }
    y += dy;
    x += dx;

    lastUseMs = clock();
}

void GameObject::Projectile::collide(GameObject* obj) {}
void GameObject::Projectile::collide(Hero* h) {}
void GameObject::Projectile::collide(Zombie* z) {}
void GameObject::Projectile::collide(Princess* p) {}
void GameObject::Projectile::collide(Projectile* p) {}
void GameObject::Projectile::collide(Dragon* d) {}
void GameObject::Projectile::collide(Trap* t) {}
void GameObject::Projectile::collide(Wall* w) {}
void GameObject::Projectile::collide(Medkit* m) {}

void GameObject::Projectile::doCollide(Hero* h) {}
void GameObject::Projectile::doCollide(Zombie* z) {}
void GameObject::Projectile::doCollide(Princess* p) {}
void GameObject::Projectile::doCollide(Projectile* p) {}
void GameObject::Projectile::doCollide(Dragon* d) {}
void GameObject::Projectile::doCollide(Trap* t) {}
void GameObject::Projectile::doCollide(Wall* w) {}
void GameObject::Projectile::doCollide(Medkit* m) {}

GameObject::Hero::Hero() : Character(HP_TABLE[getSymbOnMap()],
    DMG_TABLE[getSymbOnMap()],
    SLEEPTIME_TABLE[getSymbOnMap()]) {}

char GameObject::Hero::getSymbOnMap() {
    return 'H';
}

void GameObject::Hero::showDieMessage() {
    Visual::showMessage("YOU DIE");
}

void GameObject::Hero::incScore(const int& Add) {
    score += Add;
}

int GameObject::Hero::getScore() {
    return score;
}

void GameObject::Hero::doShot() {
    doShot_ = true;
}

void GameObject::Hero::update(GameObject*& refObj) {
    move();
    if (doShot_) {
        refObj = shot();
        doShot_ = false;
    }
}

GameObject::Projectile* GameObject::Hero::shot() {
    auto timeNow = clock();
    if (timeNow < lastShotTime + HERO_RELOAD_TIME)
        return nullptr;

    lastShotTime = timeNow;

    Projectile* p = new Projectile();
    p->setPos(y + lastDir.first, x + lastDir.second);
    p->dir(lastDir.first, lastDir.second);

    return p;
}

void GameObject::Hero::collide(GameObject* obj) {}
void GameObject::Hero::collide(Hero* h) {}
void GameObject::Hero::collide(Zombie* z) {}
void GameObject::Hero::collide(Princess* p) {}
void GameObject::Hero::collide(Projectile* p) {}
void GameObject::Hero::collide(Dragon* d) {}
void GameObject::Hero::collide(Trap* t) {}
void GameObject::Hero::collide(Wall* w) {}
void GameObject::Hero::collide(Medkit* m) {}

void GameObject::Hero::doCollide(Hero* h) {}
void GameObject::Hero::doCollide(Zombie* z) {}
void GameObject::Hero::doCollide(Princess* p) {}
void GameObject::Hero::doCollide(Projectile* p) {}
void GameObject::Hero::doCollide(Dragon* d) {}
void GameObject::Hero::doCollide(Trap* t) {}
void GameObject::Hero::doCollide(Wall* w) {}
void GameObject::Hero::doCollide(Medkit* m) {}


GameObject::Dragon::Dragon() : Enemy(HP_TABLE[getSymbOnMap()],
    DMG_TABLE[getSymbOnMap()],
    SLEEPTIME_TABLE[getSymbOnMap()]) {}

char GameObject::Dragon::getSymbOnMap() {
    return 'D';
}

void GameObject::Dragon::update(GameObject*& refObj) {
    auto dy = hero->getCoordY() - y;
    if (dy != 0) dy /= abs(dy);

    auto dx = hero->getCoordX() - x;
    if (dx != 0) dx /= abs(dx);

    if (dy == 0) {
        dir(0, dx);
        refObj = shot(0, dx);
    }
    else if (dx == 0) {
        dir(dy, 0);
        refObj = shot(dy, 0);
    }
    else if (rand() % 2) {
        dir(dy, 0);
    }
    else {
        dir(0, dx);
    }

    move();
}

GameObject::Projectile* GameObject::Dragon::shot(const int& dy, const int& dx) {
    auto timeNow = clock();
    if (timeNow < lastShotTime + DRAGON_RELOAD_TIME)
        return nullptr;

    lastShotTime = timeNow;

    Projectile* p = new Projectile();
    p->setPos(y + dy, x + dx);
    p->dir(dy, dx);

    return p;
}

void GameObject::Dragon::collide(GameObject* obj) {}
void GameObject::Dragon::collide(Hero* h) {}
void GameObject::Dragon::collide(Zombie* z) {}
void GameObject::Dragon::collide(Princess* p) {}
void GameObject::Dragon::collide(Projectile* p) {}
void GameObject::Dragon::collide(Dragon* d) {}
void GameObject::Dragon::collide(Trap* t) {}
void GameObject::Dragon::collide(Wall* w) {}
void GameObject::Dragon::collide(Medkit* m) {}

void GameObject::Dragon::doCollide(Hero* h) {}
void GameObject::Dragon::doCollide(Zombie* z) {}
void GameObject::Dragon::doCollide(Princess* p) {}
void GameObject::Dragon::doCollide(Projectile* p) {}
void GameObject::Dragon::doCollide(Dragon* d) {}
void GameObject::Dragon::doCollide(Trap* t) {}
void GameObject::Dragon::doCollide(Wall* w) {}
void GameObject::Dragon::doCollide(Medkit* m) {}


GameObject::Zombie::Zombie() : Enemy(HP_TABLE[getSymbOnMap()],
    DMG_TABLE[getSymbOnMap()],
    SLEEPTIME_TABLE[getSymbOnMap()]) {}

char GameObject::Zombie::getSymbOnMap() {
    return 'Z';
}

void GameObject::Zombie::update(GameObject*& refObj) {
    auto dy = hero->getCoordY() - y;
    if (dy != 0) dy /= abs(dy);

    auto dx = hero->getCoordX() - x;
    if (dx != 0) dx /= abs(dx);

    int rnd = rand() % 100;
    if (rnd < 15)
        dir(dy, dx);
    else if (rnd < 40)
        dir(0, dx);
    else if (rnd < 66) // 66% что шаг будет в мою сторону
        dir(dy, 0);
    else if (rnd < 84)
        dir(-dy, 0);
    else
        dir(0, -dx);

    move();
}

void GameObject::Zombie::collide(GameObject* obj) {}
void GameObject::Zombie::collide(Hero* h) {}
void GameObject::Zombie::collide(Zombie* z) {}
void GameObject::Zombie::collide(Princess* p) {}
void GameObject::Zombie::collide(Projectile* p) {}
void GameObject::Zombie::collide(Dragon* d) {}
void GameObject::Zombie::collide(Trap* t) {}
void GameObject::Zombie::collide(Wall* w) {}
void GameObject::Zombie::collide(Medkit* m) {}

void GameObject::Zombie::doCollide(Hero* h) {}
void GameObject::Zombie::doCollide(Zombie* z) {}
void GameObject::Zombie::doCollide(Princess* p) {}
void GameObject::Zombie::doCollide(Projectile* p) {}
void GameObject::Zombie::doCollide(Dragon* d) {}
void GameObject::Zombie::doCollide(Trap* t) {}
void GameObject::Zombie::doCollide(Wall* w) {}
void GameObject::Zombie::doCollide(Medkit* m) {}


GameObject::Trap::Trap() : Enemy(HP_TABLE[getSymbOnMap()],
    DMG_TABLE[getSymbOnMap()],
    SLEEPTIME_TABLE[getSymbOnMap()]) {}

char GameObject::Trap::getSymbOnMap() {
    return 'T';
}

void GameObject::Trap::collide(GameObject* obj) {}
void GameObject::Trap::collide(Hero* h) {}
void GameObject::Trap::collide(Zombie* z) {}
void GameObject::Trap::collide(Princess* p) {}
void GameObject::Trap::collide(Projectile* p) {}
void GameObject::Trap::collide(Dragon* d) {}
void GameObject::Trap::collide(Trap* t) {}
void GameObject::Trap::collide(Wall* w) {}
void GameObject::Trap::collide(Medkit* m) {}

void GameObject::Trap::doCollide(Hero* h) {}
void GameObject::Trap::doCollide(Zombie* z) {}
void GameObject::Trap::doCollide(Princess* p) {}
void GameObject::Trap::doCollide(Projectile* p) {}
void GameObject::Trap::doCollide(Dragon* d) {}
void GameObject::Trap::doCollide(Trap* t) {}
void GameObject::Trap::doCollide(Wall* w) {}
void GameObject::Trap::doCollide(Medkit* m) {}