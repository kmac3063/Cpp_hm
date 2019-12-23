#pragma once

#include "GameObject.h"

namespace GameObject {
class Subject : public GameObject {
        
};

class FixedSubject : public Subject {

};

class Projectile : public Subject {

};

class CollectItem : public Subject {
protected:
    void remove();
};

}  // namespace GameObject