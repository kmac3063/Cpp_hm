#pragma once
#include <algorithm>
#include <cmath>
#include <thread>

#include "../constants.h"
#include "../Visual.h"
#include "Character.h"
#include "Subject.h"
#include "../Options.h"

GameObject::Character::Character(const int& HP, const int& Dmg, const int64_t& SleepTimeMs) :
    hp(HP), dmg(Dmg), sleepTimeMs(SleepTimeMs * 0.9) {
    if (Options::Dif == OPTIONS_HARD) {
        dmg *= 2;
        sleepTimeMs = sleepTimeMs * 8 / 10;
    }
}

void GameObject::Character::dir(const int& dy_, const int& dx_) {
    if (dy_ != 0 || dx_ != 0)
        lastDir = { dy_, dx_ };
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
    int64_t timeNow = clock();
    if (timeNow < lastDmgMs + DAMAGE_DELAY_TIME)
        return;

    hp -= damage;
    lastDmgMs = timeNow;
}

int GameObject::Character::getDamagePower() {
    return dmg;
}

bool GameObject::Character::isAlive() {
    return hp > 0;
}

void GameObject::Character::heal(const int& heal) {
    hp = std::min(HP_TABLE['H'], hp + heal);
}

void GameObject::Character::update(std::shared_ptr<GameObject>& refObj) {
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

void GameObject::Princess::collide(std::shared_ptr<GameObject> obj) {
    obj->collide(std::shared_ptr<Princess>(this));
}
void GameObject::Princess::collide(std::shared_ptr<Hero> h) {
    doCollide(h);
    h->doCollide(std::shared_ptr<Princess>(this));
}
void GameObject::Princess::collide(std::shared_ptr<Zombie> z) {
    doCollide(z);
    z->doCollide(std::shared_ptr<Princess>(this));
}
void GameObject::Princess::collide(std::shared_ptr<Princess> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Princess>(this));
}
void GameObject::Princess::collide(std::shared_ptr<Projectile> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Princess>(this));
}
void GameObject::Princess::collide(std::shared_ptr<Dragon> d) {
    doCollide(d);
    d->doCollide(std::shared_ptr<Princess>(this));
}
void GameObject::Princess::collide(std::shared_ptr<Trap> t) {
    doCollide(t);
    t->doCollide(std::shared_ptr<Princess>(this));
}
void GameObject::Princess::collide(std::shared_ptr<Wall> w) {
    doCollide(w);
    w->doCollide(std::shared_ptr<Princess>(this));
}
void GameObject::Princess::collide(std::shared_ptr<Medkit> m) {
    doCollide(m);
    m->doCollide(std::shared_ptr<Princess>(this));
}

void GameObject::Princess::doCollide(std::shared_ptr<Hero> h) {
    setHP(0);
}
void GameObject::Princess::doCollide(std::shared_ptr<Zombie> z) {
    damage(z->getDamagePower());
}
void GameObject::Princess::doCollide(std::shared_ptr<Princess> p) {}
void GameObject::Princess::doCollide(std::shared_ptr<Projectile> p) {
    damage(p->getDamagePower());
}
void GameObject::Princess::doCollide(std::shared_ptr<Dragon> d) {
    damage(d->getDamagePower());
}
void GameObject::Princess::doCollide(std::shared_ptr<Trap> t) {
    damage(t->getDamagePower());
}
void GameObject::Princess::doCollide(std::shared_ptr<Wall> w) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Princess::doCollide(std::shared_ptr<Medkit> m) {
    heal(m->getHP());
}

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
    int64_t timeNowMs = clock();
    if (timeNowMs < lastUseMs + sleepTimeMs) {
        return;
    }
    y += dy;
    x += dx;

    lastUseMs = clock();
}

void GameObject::Projectile::collide(std::shared_ptr<GameObject> obj) {
    obj->collide(std::shared_ptr<Projectile>(this));
}
void GameObject::Projectile::collide(std::shared_ptr<Hero> h) {
    doCollide(h);
    h->doCollide(std::shared_ptr<Projectile>(this));
}
void GameObject::Projectile::collide(std::shared_ptr<Zombie> z) {
    doCollide(z);
    z->doCollide(std::shared_ptr<Projectile>(this));
}
void GameObject::Projectile::collide(std::shared_ptr<Princess> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Projectile>(this));
}
void GameObject::Projectile::collide(std::shared_ptr<Projectile> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Projectile>(this));
}
void GameObject::Projectile::collide(std::shared_ptr<Dragon> d) {
    doCollide(d);
    d->doCollide(std::shared_ptr<Projectile>(this));
}
void GameObject::Projectile::collide(std::shared_ptr<Trap> t) {
    doCollide(t);
    t->doCollide(std::shared_ptr<Projectile>(this));
}
void GameObject::Projectile::collide(std::shared_ptr<Wall> w) {
    doCollide(w);
    w->doCollide(std::shared_ptr<Projectile>(this));
}
void GameObject::Projectile::collide(std::shared_ptr<Medkit> m) {
    doCollide(m);
    m->doCollide(std::shared_ptr<Projectile>(this));
}

void GameObject::Projectile::doCollide(std::shared_ptr<Hero> h) {
    damage(h->getDamagePower());
}
void GameObject::Projectile::doCollide(std::shared_ptr<Zombie> z) {
    damage(z->getDamagePower());
}
void GameObject::Projectile::doCollide(std::shared_ptr<Princess> p) {
    damage(p->getDamagePower());
}
void GameObject::Projectile::doCollide(std::shared_ptr<Projectile> p) {
    damage(p->getDamagePower());
}
void GameObject::Projectile::doCollide(std::shared_ptr<Dragon> d) {
    damage(d->getDamagePower());
}
void GameObject::Projectile::doCollide(std::shared_ptr<Trap> t) {}
void GameObject::Projectile::doCollide(std::shared_ptr<Wall> w) {
    setHP(0);
}
void GameObject::Projectile::doCollide(std::shared_ptr<Medkit> m) {}

GameObject::Hero::Hero() : Character(HP_TABLE[getSymbOnMap()],
    DMG_TABLE[getSymbOnMap()],
    SLEEPTIME_TABLE[getSymbOnMap()]) {}

char GameObject::Hero::getSymbOnMap() {
    return 'H';
}

void GameObject::Hero::showDieMessage() {
    Visual::showMessage("YOU DIE", 5000);
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

void GameObject::Hero::update(std::shared_ptr<GameObject>& refObj) {
    move();
    if (doShot_) {
        refObj = shot();
        doShot_ = false;
    }
}

std::shared_ptr<GameObject::Projectile> GameObject::Hero::shot() {
    auto timeNow = clock();
    if (timeNow < lastShotTime + HERO_RELOAD_TIME)
        return nullptr;

    lastShotTime = timeNow;

    auto p = std::shared_ptr<Projectile>(new Projectile());
    
    auto dy = lastDir.first;
    auto dx = lastDir.second;
    if (!dx && !dy) dx = 1;

    p->setPos(y + dy, x + dx);
    p->dir(dy, dx);

    return p;
}

void GameObject::Hero::collide(std::shared_ptr<GameObject> obj) {
    obj->collide(std::shared_ptr<Hero>(this));
}
void GameObject::Hero::collide(std::shared_ptr<Hero> h) {
    doCollide(h);
    h->doCollide(std::shared_ptr<Hero>(this));
}
void GameObject::Hero::collide(std::shared_ptr<Zombie> z) {
    doCollide(z);
    z->doCollide(std::shared_ptr<Hero>(this));
}
void GameObject::Hero::collide(std::shared_ptr<Princess> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Hero>(this));
}
void GameObject::Hero::collide(std::shared_ptr<Projectile> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Hero>(this));
}
void GameObject::Hero::collide(std::shared_ptr<Dragon> d) {
    doCollide(d);
    d->doCollide(std::shared_ptr<Hero>(this));
}
void GameObject::Hero::collide(std::shared_ptr<Trap> t) {
    doCollide(t);
    t->doCollide(std::shared_ptr<Hero>(this));
}
void GameObject::Hero::collide(std::shared_ptr<Wall> w) {
    doCollide(w);
    w->doCollide(std::shared_ptr<Hero>(this));
}
void GameObject::Hero::collide(std::shared_ptr<Medkit> m) {
    doCollide(m);
    m->doCollide(std::shared_ptr<Hero>(this));
}

void GameObject::Hero::doCollide(std::shared_ptr<Hero> h) {}
void GameObject::Hero::doCollide(std::shared_ptr<Zombie> z) {
    damage(z->getDamagePower());
}
void GameObject::Hero::doCollide(std::shared_ptr<Princess> p) {
    dmg += 1000;
}
void GameObject::Hero::doCollide(std::shared_ptr<Projectile> p) {
    damage(p->getDamagePower());
}
void GameObject::Hero::doCollide(std::shared_ptr<Dragon> d) {
    damage(d->getDamagePower());
}
void GameObject::Hero::doCollide(std::shared_ptr<Trap> t) {
    damage(t->getDamagePower());
}
void GameObject::Hero::doCollide(std::shared_ptr<Wall> w) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Hero::doCollide(std::shared_ptr<Medkit> m) {
    heal(m->getHP());
}


GameObject::Dragon::Dragon() : Enemy(HP_TABLE[getSymbOnMap()],
    DMG_TABLE[getSymbOnMap()],
    SLEEPTIME_TABLE[getSymbOnMap()]) {}

char GameObject::Dragon::getSymbOnMap() {
    return 'D';
}

void GameObject::Dragon::update(std::shared_ptr<GameObject>& refObj) {
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

std::shared_ptr<GameObject::Projectile> GameObject::Dragon::shot(const int& dy, const int& dx) {
    auto timeNow = clock();
    if (timeNow < lastShotTime + DRAGON_RELOAD_TIME)
        return nullptr;

    lastShotTime = timeNow;

    auto p = std::shared_ptr<Projectile>(new Projectile());
    p->setPos(y + dy, x + dx);
    p->dir(dy, dx);

    return p;
}

void GameObject::Dragon::damage(const int& damage) {
    Character::damage(damage);
    if (hp <= 0)
        hero->incScore(1);
}


void GameObject::Dragon::collide(std::shared_ptr<GameObject> obj) {
    obj->collide(std::shared_ptr<Dragon>(this));
}
void GameObject::Dragon::collide(std::shared_ptr<Hero> h) {
    doCollide(h);
    h->doCollide(std::shared_ptr<Dragon>(this));
}
void GameObject::Dragon::collide(std::shared_ptr<Zombie> z) {
    doCollide(z);
    z->doCollide(std::shared_ptr<Dragon>(this));
}
void GameObject::Dragon::collide(std::shared_ptr<Princess> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Dragon>(this));
}
void GameObject::Dragon::collide(std::shared_ptr<Projectile> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Dragon>(this));
}
void GameObject::Dragon::collide(std::shared_ptr<Dragon> d) {
    doCollide(d);
    d->doCollide(std::shared_ptr<Dragon>(this));
}
void GameObject::Dragon::collide(std::shared_ptr<Trap> t) {
    doCollide(t);
    t->doCollide(std::shared_ptr<Dragon>(this));
}
void GameObject::Dragon::collide(std::shared_ptr<Wall> w) {
    doCollide(w);
    w->doCollide(std::shared_ptr<Dragon>(this));
}
void GameObject::Dragon::collide(std::shared_ptr<Medkit> m) {
    doCollide(m);
    m->doCollide(std::shared_ptr<Dragon>(this));
}

void GameObject::Dragon::doCollide(std::shared_ptr<Hero> h) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Dragon::doCollide(std::shared_ptr<Zombie> z) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Dragon::doCollide(std::shared_ptr<Princess> p) {
    damage(p->getDamagePower());
}
void GameObject::Dragon::doCollide(std::shared_ptr<Projectile> p) {
    damage(p->getDamagePower());
}
void GameObject::Dragon::doCollide(std::shared_ptr<Dragon> d) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Dragon::doCollide(std::shared_ptr<Trap> t) {
}
void GameObject::Dragon::doCollide(std::shared_ptr<Wall> w) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Dragon::doCollide(std::shared_ptr<Medkit> m) {}


GameObject::Zombie::Zombie() : Enemy(HP_TABLE[getSymbOnMap()],
    DMG_TABLE[getSymbOnMap()],
    SLEEPTIME_TABLE[getSymbOnMap()]) {}

char GameObject::Zombie::getSymbOnMap() {
    return 'Z';
}

void GameObject::Zombie::update(std::shared_ptr<GameObject>& refObj) {
    auto dy = hero->getCoordY() - y;
    if (dy != 0) dy /= abs(dy);

    auto dx = hero->getCoordX() - x;
    if (dx != 0) dx /= abs(dx);

    int rnd = rand() % 100;
    if (rnd < 20)
        dir(dy, dx);
    else if (rnd < 50)
        dir(0, dx);
    else if (rnd < 80) // 80% что шаг будет в мою сторону
        dir(dy, 0);
    else if (rnd < 90)
        dir(-dy, 0);
    else
        dir(0, -dx);

    move();
}

void GameObject::Zombie::damage(const int& damage) {
    Character::damage(damage);
    if (hp <= 0)
        hero->incScore(1);
}

void GameObject::Zombie::collide(std::shared_ptr<GameObject> obj) {
    obj->collide(std::shared_ptr<Zombie>(this));
}
void GameObject::Zombie::collide(std::shared_ptr<Hero> h) {
    doCollide(h);
    h->doCollide(std::shared_ptr<Zombie>(this));
}
void GameObject::Zombie::collide(std::shared_ptr<Zombie> z) {
    doCollide(z);
    z->doCollide(std::shared_ptr<Zombie>(this));
}
void GameObject::Zombie::collide(std::shared_ptr<Princess> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Zombie>(this));
}
void GameObject::Zombie::collide(std::shared_ptr<Projectile> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Zombie>(this));
}
void GameObject::Zombie::collide(std::shared_ptr<Dragon> d) {
    doCollide(d);
    d->doCollide(std::shared_ptr<Zombie>(this));
}
void GameObject::Zombie::collide(std::shared_ptr<Trap> t) {
    doCollide(t);
    t->doCollide(std::shared_ptr<Zombie>(this));
}
void GameObject::Zombie::collide(std::shared_ptr<Wall> w) {
    doCollide(w);
    w->doCollide(std::shared_ptr<Zombie>(this));
}
void GameObject::Zombie::collide(std::shared_ptr<Medkit> m) {
    doCollide(m);
    m->doCollide(std::shared_ptr<Zombie>(this));
}

void GameObject::Zombie::doCollide(std::shared_ptr<Hero> h) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Zombie::doCollide(std::shared_ptr<Zombie> z) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Zombie::doCollide(std::shared_ptr<Princess> p) {
    damage(p->getDamagePower());
}
void GameObject::Zombie::doCollide(std::shared_ptr<Projectile> p) {
    damage(p->getDamagePower());
}
void GameObject::Zombie::doCollide(std::shared_ptr<Dragon> d) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Zombie::doCollide(std::shared_ptr<Trap> t) {
    damage(t->getDamagePower());
}
void GameObject::Zombie::doCollide(std::shared_ptr<Wall> w) {
    y -= lastDir.first;
    x -= lastDir.second;
}
void GameObject::Zombie::doCollide(std::shared_ptr<Medkit> m) {}


GameObject::Trap::Trap() : Enemy(HP_TABLE[getSymbOnMap()],
    DMG_TABLE[getSymbOnMap()],
    SLEEPTIME_TABLE[getSymbOnMap()]) {}

char GameObject::Trap::getSymbOnMap() {
    return 'T';
}

void GameObject::Trap::collide(std::shared_ptr<GameObject> obj) {
    obj->collide(std::shared_ptr<Trap>(this));
}
void GameObject::Trap::collide(std::shared_ptr<Hero> h) {
    doCollide(h);
    h->doCollide(std::shared_ptr<Trap>(this));
}
void GameObject::Trap::collide(std::shared_ptr<Zombie> z) {
    doCollide(z);
    z->doCollide(std::shared_ptr<Trap>(this));
}
void GameObject::Trap::collide(std::shared_ptr<Princess> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Trap>(this));
}
void GameObject::Trap::collide(std::shared_ptr<Projectile> p) {
    doCollide(p);
    p->doCollide(std::shared_ptr<Trap>(this));
}
void GameObject::Trap::collide(std::shared_ptr<Dragon> d) {
    doCollide(d);
    d->doCollide(std::shared_ptr<Trap>(this));
}
void GameObject::Trap::collide(std::shared_ptr<Trap> t) {
    doCollide(t);
    t->doCollide(std::shared_ptr<Trap>(this));
}
void GameObject::Trap::collide(std::shared_ptr<Wall> w) {
    doCollide(w);
    w->doCollide(std::shared_ptr<Trap>(this));
}
void GameObject::Trap::collide(std::shared_ptr<Medkit> m) {
    doCollide(m);
    m->doCollide(std::shared_ptr<Trap>(this));
}

void GameObject::Trap::doCollide(std::shared_ptr<Hero> h) {
    damage(h->getDamagePower());
}
void GameObject::Trap::doCollide(std::shared_ptr<Zombie> z) {
    damage(z->getDamagePower());
}
void GameObject::Trap::doCollide(std::shared_ptr<Princess> p) {
    setHP(0);
}
void GameObject::Trap::doCollide(std::shared_ptr<Projectile> p) {}
void GameObject::Trap::doCollide(std::shared_ptr<Dragon> d) {
    damage(d->getDamagePower());
}
void GameObject::Trap::doCollide(std::shared_ptr<Trap> t) {}
void GameObject::Trap::doCollide(std::shared_ptr<Wall> w) {}
void GameObject::Trap::doCollide(std::shared_ptr<Medkit> m) {}