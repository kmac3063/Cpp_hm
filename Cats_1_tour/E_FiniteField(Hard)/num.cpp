#include "num.h"

#include <cstdint>

Num::Num(int val, int mod) : value(val), modulo(mod) {
    if (modulo != 0)
        value %= modulo;
}

Num& Num::operator=(const Num& other) {
    value = other.value;
    modulo = other.modulo;
    return *this;
}

Num Num::operator+(const Num& other) {
    Num a(value, modulo);

    int64_t val = (int64_t)a.value + other.value;
    if (modulo != 0)
        val %= a.modulo;

    a.value = static_cast<int>(val);

    return a;
}
Num Num::operator-(const Num& other) {
    Num a(value, modulo);

    int64_t val = (int64_t)a.value - other.value;
    while (val < 0)
        val += modulo;
    if (modulo != 0)
        val %= a.modulo;

    a.value = static_cast<int>(val);

    return a;
}
Num Num::operator*(const Num& other) {
    Num a(value, modulo);

    int64_t val = (int64_t)a.value * other.value;
    if (modulo != 0)
        val %= a.modulo;

    a.value = static_cast<int>(val);

    return a;
}

Num Num::operator+(int num) {
    Num a(value, modulo);

    int64_t val = (int64_t)a.value + num;
    if (modulo != 0)
        val %= a.modulo;

    a.value = static_cast<int>(val);

    return a;
}
Num Num::operator-(int num) {
    Num a(value, modulo);

    int64_t val = (int64_t)a.value - num;
    while (val < 0)
        val += modulo;
    if (modulo != 0)
        val %= a.modulo;

    a.value = static_cast<int>(val);

    return a;
}
Num Num::operator*(int num) {
    Num a(value, modulo);

    int64_t val = (int64_t)a.value * num;
    if (modulo != 0)
        val %= a.modulo;

    a.value = static_cast<int>(val);

    return a;
}

Num& Num::operator+=(const Num& other) {
    int64_t val = (int64_t)value + other.value;
    if (modulo != 0)
        val %= modulo;

    value = static_cast<int>(val);

    return *this;
}
Num& Num::operator-=(const Num& other) {
    int64_t val = (int64_t)value - other.value;
    while (val < 0)
        val += modulo;
    if (modulo != 0)
        val %= modulo;

    value = static_cast<int>(val);

    return *this;
}
Num& Num::operator*=(const Num& other) {
    int64_t val = (int64_t)value * other.value;
    if (modulo != 0)
        val %= modulo;

    value = static_cast<int>(val);

    return *this;
}
Num& Num::operator+=(int num) {
    int64_t val = (int64_t)value + num;
    if (modulo != 0)
        val %= modulo;

    value = static_cast<int>(val);

    return *this;
}
Num& Num::operator-=(int num) {
    int64_t val = (int64_t)value - num;
    while (val < 0)
        val += modulo;
    if (modulo != 0)
        val %= modulo;

    value = static_cast<int>(val);

    return *this;
}
Num& Num::operator*=(int num) {
    int64_t val = (int64_t)value * num;
    if (modulo != 0)
        val %= modulo;

    value = static_cast<int>(val);

    return *this;
}

int value;
int modulo;
