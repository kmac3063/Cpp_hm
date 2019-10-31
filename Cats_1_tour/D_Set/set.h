#pragma once

#include <vector>

class Set {
 private:
    std::vector<int64_t> v;

 public:
    explicit Set(const std::vector<int64_t> vector) {
        for (size_t i = 0; i < vector.size(); i++) {
            bool next = false;
            for (size_t j = 0; j < v.size(); j++) {
                if (v[j] == vector[i]) next = true;
            }
            if (next) continue;
            v.push_back(vector[i]);
        }
    }

    Set() = default;

    Set Union(const Set& a) const {
        Set t(a.Data());
        for (auto& i : Data())
            if (!t.Contains(i))
                t.Add(i);
        return t;
    }

    Set Intersection(const Set& a) const {
        Set t(Data());
        for (auto& i : Data())
            if (!a.Contains(i))
                t.Remove(i);
        return t;
    }

    Set Difference(const Set& a) const {
        Set t(Data());
        for (auto& i : Data())
            if (a.Contains(i))
                t.Remove(i);
        return t;
    }

    Set SymmetricDifference(const Set& a) const {
        Set t = Difference(a).Union(a.Difference(*this));
        return t;
    }

    void Add(int64_t a) {
        if (!Contains(a)) v.push_back(a);
    }

    void Remove(int64_t a) {
        std::vector<int64_t> t;
        for (auto& i : v)
            if (i != a)
                t.push_back(i);
        v = t;
    }

    bool Contains(int64_t a) const {
        for (auto& i : v)
            if (i == a) return true;
        return false;
    }

    std::vector<int64_t> Data() const {
        return v;
    }
};
