#pragma once
#include <unordered_map>

template<typename Vertex>
class BfsVisitor {
 public:
    BfsVisitor() {
        core = new Core();
    }

    BfsVisitor(const BfsVisitor& a) {
        if (a.core != nullptr) {
            core = a.core;
            core->counter++;
        }
    }

    ~BfsVisitor() {
        if (core == nullptr)
            return;

        if (--core->counter == 0)
            delete core;
    }

    void ExamineVertex(const Vertex& vertex) {  // pop
        core->last = vertex;
    }

    void DiscoverVertex(const Vertex& vertex) {  // put
        if (core->distance.count(core->last) == 0) {
            core->start = vertex;
            core->last = vertex;
            core->distance[vertex] = -1;
        }
        core->parent[vertex] = core->last;
        core->distance[vertex] = core->distance[core->last] + 1;
    }

    size_t DistanceTo(const Vertex& target) const {
        return core->distance[target];
    }
    Vertex Parent(const Vertex& vertex) const {
        return core->parent[vertex];
    }

 private:
    class Core {
     public:
        Core() {
            counter = 1;
        }

        std::unordered_map<Vertex, Vertex> parent;
        std::unordered_map<Vertex, size_t> distance;
        Vertex start;
        Vertex last;
        size_t counter;
    };
    Core* core;
};
