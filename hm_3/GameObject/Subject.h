#pragma once

#include "GameObject.h"

namespace GameObject {
class Subject : public GameObject {
        
};

class Wall : public Subject {
    virtual char getSymbOnMap() {
        return '#';
    }
};

class Medkit : public Subject {
    virtual char getSymbOnMap() {
        return '+';
    }
};

}  // namespace GameObject