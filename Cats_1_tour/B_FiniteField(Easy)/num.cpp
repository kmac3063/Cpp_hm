#include "num.h"

Num::Num(int val, int mod) : value(val), modulo(mod) {
    if (mod != 0)
        value %= mod;
}

Num::Num(const Num& other): value(other.value), modulo(0) {}
