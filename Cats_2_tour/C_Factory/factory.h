#pragma once

#include <map>
#include <string>

class Object {
 public:
    virtual std::string ToString() const = 0;
    virtual ~Object() {}
};

class Apple : public Object {
 public:
    std::string ToString() const {
        return "apple!";
    }
};

Object* createApple() {
    return new Apple;
}


class List : public Object {
 public:
    std::string ToString() const {
        return "list";
    }
};

Object* createList() {
    return new List;
}

class Yai : public Object {
 public:
    std::string ToString() const {
        return "yet another identifier";
    }
};

Object* createYai() {
    return new Yai;
}

class Factory {
 private:
     std::map<std::string, Object * (*)()> map;
 public:
     Factory() {
         Apple a;
         List l;
         Yai y;
         Register(a.ToString(), createApple);
         Register(l.ToString(), createList);
         Register(y.ToString(), createYai);
     }

     Object* Create(const std::string& class_id) {
         return map[class_id]();
     }

     void Register(const std::string& class_id, Object* (*instance_creator)()) {
         map[class_id] = instance_creator;
     }
};
