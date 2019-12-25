#pragma once
#include <map>
#include "GameObject.h"

GameObject::Hero* GameObject::hero;
std::map<char, int> GameObject::HP_TABLE;
std::map<char, int> GameObject::DMG_TABLE;
std::map<char, int64_t> GameObject::SLEEPTIME_TABLE;

void GameObject::GameObject::setPos(const int& y_, const int& x_) {
    y = y_;
    x = x_;
}
int GameObject::GameObject::getCoordY() { return y; }
int GameObject::GameObject::getCoordX() { return x; }


