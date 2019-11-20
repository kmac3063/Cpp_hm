#include "hash_map.hpp"
#include <iostream>

using namespace std;

int main() {
    fefu::hash_map<int, int> M(10);
    
    M[1] = 1;
    M[100] = 2;
    M[1000] = 3;

    cout << M.at(1) << " " << M.at(1000) << '\n';
    M.at(2);

    return 0;
}