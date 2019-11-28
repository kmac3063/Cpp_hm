
#include <vector>
#include <string>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <deque>

#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <type_traits>
#include <functional>
#include <utility>
#include <atomic>
#include <thread>
#include <future>
#include <chrono>
#include <iterator>
#include <memory>

#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"
#include "hash_map.hpp"

using namespace fefu;
using namespace std;

TEST_CASE("constructor()") {
    hash_map<int, int> a;
    REQUIRE(a.bucket_count() == 0);
    REQUIRE(a.size() == 0);
    REQUIRE(a.begin() == a.end());
    REQUIRE(a.empty() == true);
}

TEST_CASE("constructor(n)") {
    hash_map<string, string> a(10);
    REQUIRE(a.bucket_count() == 10);
    REQUIRE(a.size() == 0);
    REQUIRE(a.begin() == a.end());
    REQUIRE(a.empty() == true);
}

TEST_CASE("constructor(first it, last it)") {
    unordered_map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    hash_map<int, int> a(m.begin(), m.end());

    REQUIRE(a.size() == 3);
    REQUIRE(a.bucket_count() == 7);
    REQUIRE(a.begin() != a.end());
    REQUIRE(a.empty() == 0);
}

TEST_CASE("constructor(hash_m) copy") {
    unordered_map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[4] = 4;
    m[5] = 5;
    hash_map<int, int> a(m.begin(), m.end());
    hash_map<int, int> b(a);

    REQUIRE(b.size() == 5);
    REQUIRE(b.bucket_count() == 11);
    REQUIRE(b.begin()->first == 1);
    REQUIRE(b.begin()->second == 1);
    REQUIRE(b.begin() != a.begin());
    REQUIRE(b.end() != a.end());
    REQUIRE(b.begin() != b.end());
    REQUIRE(b.empty() == 0);
}

TEST_CASE("constructor(hash_m) move") {
    unordered_map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[4] = 4;
    m[5] = 5;
    hash_map<int, int> a(m.begin(), m.end());
    hash_map<int, int> b(std::move(a));

    REQUIRE(b.size() == 5);
    REQUIRE(b.bucket_count() == 11);
    REQUIRE(b.begin() != a.begin());
    REQUIRE(b.end() != a.end());
    REQUIRE(b.begin() != b.end());
    REQUIRE(b.empty() == 0);
}

TEST_CASE("constructor(hash_m, a) copy") {
    unordered_map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[4] = 4;
    m[5] = 5;
    hash_map<int, int> a(m.begin(), m.end());

    auto al = fefu::allocator<std::pair<const int, int>>();
    al.setSeed(101);
    hash_map<int, int> b(a, al);

    REQUIRE(b.size() == 5);
    REQUIRE(b.bucket_count() == 11);
    REQUIRE(b.begin()->first == 1);
    REQUIRE(b.begin()->second == 1);
    REQUIRE(b.begin() != a.begin());
    REQUIRE(b.end() != a.end());
    REQUIRE(b.begin() != b.end());
    REQUIRE(b.empty() == 0);

    REQUIRE(al.getSeed() == b.get_allocator().getSeed());
}

TEST_CASE("constructor(hash_m, a) move") {
    unordered_map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[4] = 4;
    m[5] = 5;
    hash_map<int, int> a(m.begin(), m.end());

    auto al = fefu::allocator<std::pair<const int, int>>();
    al.setSeed(0x1010);
    hash_map<int, int> b(std::move(a), al);

    REQUIRE(b.size() == 5);
    REQUIRE(b.bucket_count() == 11);
    REQUIRE(b.begin() != a.begin());
    REQUIRE(b.end() != a.end());
    REQUIRE(b.begin() != b.end());
    REQUIRE(b.empty() == 0);

    REQUIRE(al.getSeed() == b.get_allocator().getSeed());
}

TEST_CASE("constructor(init_list)") {
    initializer_list<pair<const string, string>> l = { {"olo", "1"}, {"ala", "2"} };
    hash_map<string, string> a(l);

    REQUIRE(a.size() == 2);
    REQUIRE(a.bucket_count() == 5);
    REQUIRE(a["olo"] == "1");
    REQUIRE(a["ala"] == "2");
}

TEST_CASE("oper '=' copy") {
    unordered_map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[4] = 4;
    m[5] = 5;
    hash_map<int, int> a(m.begin(), m.end());

    hash_map<int, int> b = a;

    REQUIRE(b.size() == 5);
    REQUIRE(b.bucket_count() == 11);
    REQUIRE(b.begin()->first == 1);
    REQUIRE(b.begin()->second == 1);
    REQUIRE(b.begin() != a.begin());
    REQUIRE(b.end() != a.end());
    REQUIRE(b.begin() != b.end());
    REQUIRE(b.empty() == 0);
}

TEST_CASE("oper '=' move") {
    unordered_map<int, int> m;
    m[1] = 1;
    m[2] = 2;
    m[3] = 3;
    m[4] = 4;
    m[5] = 5;
    hash_map<int, int> a(m.begin(), m.end());
    hash_map<int, int> b = std::move(a);

    REQUIRE(b.size() == 5);
    REQUIRE(b.bucket_count() == 11);
    REQUIRE(b.begin() != a.begin());
    REQUIRE(b.end() != a.end());
    REQUIRE(b.begin() != b.end());
    REQUIRE(b.empty() == 0);
}

TEST_CASE("oper '=' init_list") {
    initializer_list<pair<const string, string>> l = { {"olo", "1"}, {"KKK", "WWW"}, {"ala", "2"} };
    hash_map<string, string> a(l);

    REQUIRE(a.size() == 3);
    REQUIRE(a.bucket_count() == 7);
    REQUIRE(a["olo"] == "1");
    REQUIRE(a["ala"] == "2");
    REQUIRE(a["KKK"] == "WWW");
}

TEST_CASE("get_allocator") {
    initializer_list<pair<const string, string>> l = { {"olo", "1"}, {"KKK", "WWW"}, {"ala", "2"} };
    hash_map<string, string> a(l);

    fefu::allocator<pair<const string, string>> alloc;
    alloc.setSeed(010203);
    hash_map<string, string> b(a, alloc);

    REQUIRE(alloc.getSeed() == b.get_allocator().getSeed());
}

TEST_CASE("empty") {
    hash_map<string, string> a = { {"olo", "1"}, {"KKK", "WWW"}, {"ala", "2"} };
    hash_map<string, string> b;
    hash_map<string, string> c = {};

    REQUIRE(a.empty() == false);
    REQUIRE(b.empty() == true);
    REQUIRE(c.empty() == true);
}

TEST_CASE("size") {
    hash_map<string, string> a = { {"olo", "1"}, {"KKK", "WWW"}, {"ala", "2"} };
    hash_map<string, string> b;
    hash_map<char, char> c(1000);
    for (int i = 0; i < 100; i++)
    {
        c[i] = i * 2;
    }

    REQUIRE(a.size() == 3);
    REQUIRE(b.size() == 0);
    REQUIRE(c.size() == 100);
}

TEST_CASE("max_size") {
    hash_map<string, string> a = { {"olo", "1"}, {"KKK", "WWW"}, {"ala", "2"} };

    REQUIRE(a.max_size() == UINT32_MAX);
}

TEST_CASE("begin iterator") {
    hash_map<string, string> a = { {"olo", "1"} };
    hash_map_iterator it = a.begin();

    REQUIRE(it == a.begin());
    REQUIRE(*it == *a.begin());
    REQUIRE(it->first == "olo");
    REQUIRE(it->second == "1");
}

TEST_CASE("begin const_iterator") {
    const hash_map<string, string> a = { {"olo", "1"} };
    hash_map_const_iterator it = a.begin();

    REQUIRE(it == a.begin());
    REQUIRE(*it == *a.begin());
    REQUIRE(it->first == "olo");
    REQUIRE(it->second == "1");
}

TEST_CASE("cbegin const_iterator") {
    const hash_map<string, string> a = { {"olo", "1"} };
    hash_map_const_iterator it = a.cbegin();

    REQUIRE(it == a.cbegin());
    REQUIRE(*it == *a.cbegin());
    REQUIRE(it->first == "olo");
    REQUIRE(it->second == "1");
}

TEST_CASE("end iterator") {
    hash_map<string, string> a = { {"olo", "1"} };
    hash_map<string, string> b = { {"olo", "1"}, {"AAA", "BBB"} };
    hash_map<string, string> c = { {"AAA", "BBB"},  {"CCC", "WWW"}, {"KRA", "BRA"} };

    REQUIRE(a.end() != b.end());
    REQUIRE(a.end() == a.end());
    REQUIRE(++a.begin() == a.end());
    REQUIRE(a.end() != b.end());
    REQUIRE(a.end() != c.end());
}

TEST_CASE("end const_iterator") {
    const hash_map<string, string> a = { {"olo", "1"} };
    const hash_map<string, string> b = { {"olo", "1"}, {"AAA", "BBB"} };
    const hash_map<string, string> c = { {"AAA", "BBB"},  {"CCC", "WWW"}, {"KRA", "BRA"} };

    REQUIRE(a.end() != b.end());
    REQUIRE(a.end() == a.end());
    REQUIRE(++a.begin() == a.end());
    REQUIRE(a.end() != b.end());
    REQUIRE(a.end() != c.end());
}

TEST_CASE("cend const_iterator") {
    const hash_map<string, string> a = { {"olo", "1"} };
    const hash_map<string, string> b = { {"olo", "1"}, {"AAA", "BBB"} };
    const hash_map<string, string> c = { {"AAA", "BBB"},  {"CCC", "WWW"}, {"KRA", "BRA"} };

    REQUIRE(a.cend() != b.cend());
    REQUIRE(a.cend() == a.cend());
    REQUIRE(++a.cbegin() == a.cend());
    REQUIRE(a.cend() != b.cend());
    REQUIRE(a.cend() != c.cend());
}

TEST_CASE("insert(value)") {
    set<pair<const int, int>> s = { {10, 1}, {20, 2}, {30, 3}, {40, 4}, {50, 5} };
    hash_map<int, int> a(s.begin(), s.end());

    REQUIRE(a.size() == 5);
    REQUIRE(a.bucket_count() == 11);

    pair<const int, int> p = { 100, 10 };
    a.insert(p);

    REQUIRE(a.size() == 6);
    REQUIRE(a.bucket_count() == 11);

    a.insert(p);

    REQUIRE(a.size() == 6);
    REQUIRE(a.bucket_count() == 11);

    auto st = s;
    st.clear();
    for (auto it = a.begin(); it != a.end(); it++)
        st.insert(*it);

    REQUIRE(st != s);
    s.insert({ 100, 10 });
    REQUIRE(st == s);
}

TEST_CASE("insert(value) move") {
    set<pair<const int, int>> s = { {10, 1}, {20, 2}, {30, 3}, {40, 4}, {50, 5} };
    hash_map<int, int> a(s.begin(), s.end());

    REQUIRE(a.size() == 5);
    REQUIRE(a.bucket_count() == 11);

    pair<const int, int> p = { 100, 10 };
    a.insert(std::move(p));

    REQUIRE(a.size() == 6);
    REQUIRE(a.bucket_count() == 11);

    a.insert(std::move(p));

    REQUIRE(a.size() == 6);
    REQUIRE(a.bucket_count() == 11);

    auto st = s;
    st.clear();
    for (auto it = a.begin(); it != a.end(); it++)
        st.insert(*it);

    REQUIRE(st != s);
    s.insert({ 100, 10 });
    REQUIRE(st == s);
}

TEST_CASE("insert (first it, last it)") {
    set<pair<const int, int>> s = { {10, 1}, {20, 2}, {30, 3}, {40, 4}, {50, 5} };
    hash_map<int, int> a;
    a.insert(s.begin(), s.end());

    REQUIRE(a.size() == s.size());
    for (auto el : s) {
        REQUIRE(a[el.first] == el.second);
    }
}

TEST_CASE("insert init list") {
    initializer_list<pair<const int, int>> l = { {10, 1}, {20, 2}, {30, 3}, {40, 4}, {50, 5} };
    hash_map<int, int> a;
    a.insert(l);

    REQUIRE(a.size() == l.size());
    for (auto el : l) {
        REQUIRE(a[el.first] == el.second);
    }

    a.insert(l);

    REQUIRE(a.size() == l.size());
    for (auto el : l) {
        REQUIRE(a[el.first] == el.second);
    }

    a.insert({ 1, 1 });

    a.insert(l);

    REQUIRE(a.size() - 1 == l.size());
    for (auto el : l) {
        REQUIRE(a[el.first] == el.second);
    }
}

TEST_CASE("insert or assign") {
    initializer_list<pair<const int, int>> l = { {10, 1}, {20, 2}, {30, 3}, {40, 4}, {50, 5} };
    hash_map<int, int> a;
    a.insert(l);

    REQUIRE(a.size() == l.size());
    for (auto el : l) {
        REQUIRE(a[el.first] == el.second);
    }

    pair<const int, int> g = { 1, 10 };
    auto r = a.insert_or_assign(g.first, g.second);
    REQUIRE(r.second == true);
    r = a.insert_or_assign(g.first, g.second);
    REQUIRE(r.second == false);

    a.insert_or_assign(1, 1);

    REQUIRE(a.size() == l.size() + 1);
}

TEST_CASE("insert or assign move") {
    initializer_list<pair<const int, int>> l = { {10, 1}, {20, 2}, {30, 3}, {40, 4}, {50, 5} };
    hash_map<int, int> a;
    a.insert(l);

    REQUIRE(a.size() == l.size());
    for (auto el : l) {
        REQUIRE(a[el.first] == el.second);
    }

    pair<const int, int> g = { 1, 10 };
    auto r = a.insert_or_assign(g.first, std::move(g.second));
    REQUIRE(r.second == true);
    pair<const int, int> c = { 1, 20 };
    r = a.insert_or_assign(c.first, std::move(c.second));
    REQUIRE(r.second == false);

    a.insert_or_assign(1, 1);

    REQUIRE(a.size() == l.size() + 1);
}

TEST_CASE("erase const_it") {
    hash_map<char, char> b = { {'a', 'b'} };
    hash_map<char, char> c = { {'d', 'v'} };


    hash_map_const_iterator it = c.begin();
    REQUIRE(b.erase(it) == b.end());
    REQUIRE(b.size() == 1);

    hash_map_const_iterator it1 = b.begin();
    b.erase(it1);
    REQUIRE(b.begin() == b.end());
    REQUIRE(b.size() == 0);
}


TEST_CASE("erase it") {
    hash_map<char, char> b = { {'a', 'b'} };
    hash_map<char, char> c = { {'d', 'v'} };


    hash_map_iterator it = c.begin();
    REQUIRE(b.erase(it) == b.end());
    REQUIRE(b.size() == 1);

    hash_map_iterator it1 = b.begin();
    b.erase(it1);
    REQUIRE(b.begin() == b.end());
    REQUIRE(b.size() == 0);
}

TEST_CASE("erase key") {
    hash_map<int, int> a;

    for (int i = 0; i < 1000; i++)
    {
        a.insert({ i, i * i });
    }
    REQUIRE(a.size() == 1000);

    for (int i = 0; i < 1000; i++)
    {
        REQUIRE(a.erase(i) == 1);
        REQUIRE(a.size() == 999 - i);
    }
}

TEST_CASE("erase (first it, last it)") {
    hash_map<int, int> a = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
    hash_map<int, int> b = { {3, 3}, {4, 4} };

    a.erase(b.begin(), b.end());
    REQUIRE(a.size() == 3);

    set<pair<int, int>> s = { {1, 1}, {2, 2}, {5, 5} };
    set<pair<int, int>> st;
    for (auto it = a.begin(); it != a.end(); it++) {
        st.insert(*it);
    }
    REQUIRE(st == s);

    b.erase(b.begin(), b.end());
    REQUIRE(b.empty() == true);
}

TEST_CASE("clear") {
    hash_map<int, int> a = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

    a.clear();

    REQUIRE(a.empty() == true);
    REQUIRE(a.begin() == a.end());
}

TEST_CASE("swap") {
    fefu::allocator<pair<const int, int>> al_1;
    al_1.setSeed(101);
    hash_map<int, int> a(al_1);
    a.insert({ {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} });

    fefu::allocator<pair<const int, int>> al_2;
    al_2.setSeed(202);
    hash_map<int, int> b(al_2);
    b.insert({ {6, 6}, {7, 7} });

    a.swap(b);

    REQUIRE(a.size() == 2);
    REQUIRE(b.size() == 5);
    REQUIRE(a.find(6) != a.end());
    REQUIRE(a.find(7) != a.end());

    REQUIRE(a.begin() != b.begin());
    REQUIRE(a.get_allocator().getSeed() == 202);
    REQUIRE(b.get_allocator().getSeed() == 101);
}

TEST_CASE("find") {
    hash_map<string, int> a = { {"A", 1}, {"B", 2}, {"C", 3}, {"D", 4}, {"E", 5} };
    REQUIRE(a.find("A") != a.end());
    REQUIRE(a.find("B") != a.end());
    REQUIRE(a.find("C") != a.end());
    REQUIRE(a.find("F") == a.end());
    REQUIRE(a.find("GAS") == a.end());

    a.insert({ "GA", 20 });
    a.insert({ "GO", 30 });

    REQUIRE(a.find("GA") != a.end());
    REQUIRE(a.find("GO") != a.end());

    a.erase("GA");
    REQUIRE(a.find("GA") == a.end());
}

TEST_CASE("find const") {
    const hash_map<string, int> a = { {"A", 1}, {"B", 2}, {"C", 3}, {"D", 4}, {"E", 5} };
    REQUIRE(a.find("A") != a.end());
    REQUIRE(a.find("B") != a.end());
    REQUIRE(a.find("C") != a.end());
    REQUIRE(a.find("F") == a.end());
    REQUIRE(a.find("GAS") == a.end());
    REQUIRE(a.find("GA") == a.end());
}

TEST_CASE("count") {
    hash_map<string, int> a = { {"A", 1}, {"B", 2}, {"C", 3}, {"D", 4}, {"E", 5} };
    REQUIRE(a.count("A") == 1);
    REQUIRE(a.count("B") == 1);
    REQUIRE(a.count("C") == 1);
    REQUIRE(a.count("F") == 0);
    REQUIRE(a.count("GAS") == 0);

    a.insert({ "GA", 20 });
    a.insert({ "GO", 30 });

    REQUIRE(a.count("GA") == 1);
    REQUIRE(a.count("GO") == 1);

    a.erase("GA");
    REQUIRE(a.count("GA") == 0);
}

TEST_CASE("contains") {
    hash_map<string, int> a = { {"A", 1}, {"B", 2}, {"C", 3}, {"D", 4}, {"E", 5} };
    REQUIRE(a.contains("A") == 1);
    REQUIRE(a.contains("B") == 1);
    REQUIRE(a.contains("C") == 1);
    REQUIRE(a.contains("F") == 0);
    REQUIRE(a.contains("GAS") == 0);

    a.insert({ "GA", 20 });
    a.insert({ "GO", 30 });

    REQUIRE(a.contains("GA") == 1);
    REQUIRE(a.contains("GO") == 1);

    a.erase("GA");
    REQUIRE(a.contains("GA") == 0);
}

TEST_CASE("[]") {
    hash_map<string, int> a = { {"A", 1}, {"B", 2}, {"C", 3}, {"D", 4}, {"E", 5} };
    int t = 1;
    REQUIRE(a["A"] == t++);
    REQUIRE(a["B"] == t++);
    REQUIRE(a["C"] == t++);
    REQUIRE(a["D"] == t++);
    REQUIRE(a["E"] == t++);
    REQUIRE(a["F"] == 0);

    a.insert({ "RAZA", t });
    REQUIRE(a["RAZA"] == t);
}

TEST_CASE("[] move") {
    hash_map<string, int> a = { {"A", 1}, {"B", 2}, {"C", 3}, {"D", 4}, {"E", 5} };
    int t = 1;
    REQUIRE(a["A"] == t++);
    REQUIRE(a["B"] == t++);
    REQUIRE(a["C"] == t++);
    REQUIRE(a["D"] == t++);
    REQUIRE(a["E"] == t++);
    REQUIRE(a["F"] == 0);
}

TEST_CASE("at") {
    hash_map<string, int> a = { {"A", 1}, {"B", 2}, {"C", 3}, {"D", 4}, {"E", 5} };
    int t = 1;
    REQUIRE(a.at("A") == t++);
    REQUIRE(a.at("B") == t++);
    REQUIRE(a.at("C") == t++);
    REQUIRE(a.at("D") == t++);
    REQUIRE(a.at("E") == t++);

    a["RAZA"] = t;
    REQUIRE(a.at("RAZA") == t);
}

TEST_CASE("at const") {
    const hash_map<string, int> a = { {"A", 1}, {"B", 2}, {"C", 3}, {"D", 4}, {"E", 5} };
    int t = 1;
    REQUIRE(a.at("A") == t++);
    REQUIRE(a.at("B") == t++);
    REQUIRE(a.at("C") == t++);
    REQUIRE(a.at("D") == t++);
    REQUIRE(a.at("E") == t++);
}

TEST_CASE("rehash") {
    hash_map<int, int> mapa;
    REQUIRE(mapa.bucket_count() == 0);

    mapa.rehash(3);
    mapa[1] = 2;
    mapa[2] = 3;
    mapa[3] = 4;
    REQUIRE(mapa.bucket_count() == 7);
    mapa.rehash(3);
    REQUIRE(mapa.bucket_count() == 7);

    mapa.rehash(112);
    REQUIRE(mapa.bucket_count() == 113);
}

TEST_CASE("oper ==") {
    hash_map<int, int> mapa1 = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };
    hash_map<int, int> mapa2 = { {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5} };

    REQUIRE((mapa1 == mapa2) == true);
    hash_map<int, int> mapa3 = { {1, 1}, {3, 3}, {4, 4} };
    REQUIRE((mapa1 == mapa3) == false);

    mapa3[2] = 2;
    mapa3[5] = 5;
    REQUIRE((mapa1 == mapa2) == true);
}