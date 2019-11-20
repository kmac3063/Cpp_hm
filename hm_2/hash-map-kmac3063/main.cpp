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

    for (auto it = M.begin(); it != M.end(); it++) {
        cout << it->first << " " << it->second << '\n';
    }

    return 0;
}