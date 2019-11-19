#pragma once

#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>
#include <algorithm>


using std::vector;
using std::string;
using std::map;
using std::unordered_map;
using std::set;

class GameDatabase {
 public:
    GameDatabase() = default;

    void Insert(ObjectId id, string name, size_t x, size_t y) {
        GameObject n;
        n.id = id;
        n.name = name;
        n.x = x;
        n.y = y;

        Remove(id);

        map_id[id] = n;
        map_name[name].insert(id);
        map_coord[{x, y}].insert(id);
    }

    void Remove(const ObjectId& id) {
        if (map_id.count(id) == 0)
            return;

        auto& obj = map_id[id];

        map_name[obj.name].erase(id);
        map_coord[{obj.x, obj.y}].erase(id);
        map_id.erase(id);
    }

    vector<GameObject> DataByName(string name) const {
        if (map_name.count(name) == 0)
            return vector<GameObject>();

        vector<GameObject> v;
        for (auto o : map_name.at(name)) {
            v.push_back(map_id.at(o));
        }

        return v;
    }

    vector<GameObject> DataByPosition(size_t x, size_t y) const {
        if (map_coord.count({ x, y }) == 0)
            return vector<GameObject>();

        vector<GameObject> v;
        for (auto o : map_coord.at({ x, y })) {
            v.push_back(map_id.at(o));
        }

        return v;
    }

    vector<GameObject> Data() const {
        vector<ObjectId> s;
        for (auto i : map_id)
            s.push_back(i.first);

        vector<GameObject> v;
        for (size_t i = s.size(); i > 0; i--) {
            v.push_back(map_id.at(s[i - 1]));
        }

        return v;
    }

 private:
     struct cmp {
         bool operator () (const ObjectId& a, const ObjectId& b) const {
             return (a > b);
         }
     };

    map <string, set <ObjectId, cmp>> map_name;
    map <std::pair<size_t, size_t>, set <ObjectId, cmp>> map_coord;
    map <ObjectId, GameObject> map_id;
};
