#include "hash_map.hpp"
#include <iostream>
#include <map>

using namespace std;

int main() {
    fefu::hash_map<int, int> M(103);
    
    for (int i = 0; i < 10; i++)
    {
        M[i] = i + 10;
    }

    auto it1 = M.begin();
    int a1 = it1->first, a2 = it1->second;
    
    auto it2 = ++it1;
    a1 = it2->first, a2 = it2->second;
    
    auto it3 = ++it2;
    a1 = it3->first, a2 = it3->second;

    int i = 0;
    for (auto it = M.begin(); it != M.end(); it++) {
        cout << it->first << " " << it->second << '\n';
        i++;
    }

    return 0;
}