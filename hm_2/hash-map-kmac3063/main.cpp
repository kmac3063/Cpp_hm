#include "hash_map.hpp"
#include <iostream>
#include <map>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "../../catch.hpp"

using namespace fefu;

TEST_CASE("Constructor") {
    hash_map<int, int> map1(10);
    hash_map<int, int> map2(10);
    map1.insert({ 3, 3 });
    REQUIRE(map1.at(3) == 3);
}