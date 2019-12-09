#pragma once

#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <iostream>

struct map_tag;
struct set_tag;
struct prim_tag;

template <typename T>
struct ContainerType {
    static const char type_id = 0;
    typedef prim_tag tag;
};

template <typename K, typename V>
struct ContainerType <std::map<K, V>> {
    static const char type_id = 1;
    typedef map_tag tag;
};
template <typename K, typename V>
struct ContainerType <std::multimap<K, V>> {
    static const char type_id = 2;
    typedef map_tag tag;
};
template <typename K, typename V>
struct ContainerType <std::unordered_map<K, V>> {
    static const char type_id = 3;
    typedef map_tag tag;
};
template <typename K, typename V>
struct ContainerType <std::unordered_multimap<K, V>> {
    static const char type_id = 4;
    typedef map_tag tag;
};

template <typename K>
struct ContainerType <std::set<K>> {
    static const char type_id = 10;
    typedef set_tag tag;
};

template <typename K>
struct ContainerType <std::multiset<K>> {
    static const char type_id = 20;
    typedef set_tag tag;
};

template <typename K>
struct ContainerType <std::unordered_set<K>> {
    static const char type_id = 30;
    typedef set_tag tag;
};

template <typename K>
struct ContainerType <std::unordered_multiset<K>> {
    static const char type_id = 40;
    typedef set_tag tag;
};



template<typename Tag1, typename Tag2>
struct Merge {
    template<class C1, class C2>
    static bool merge(C1* c1, const C2& c2) {
        return true;
    }
};

template<>
struct Merge<map_tag, map_tag> {
    template<class C1, class C2>
    static bool merge(C1* c1, const C2& c2) {
        typedef typename
            std::remove_cv<typename C1::key_type>::type no_cv_key_t1;
        typedef typename
            std::remove_reference<no_cv_key_t1>::type no_cvr_key_t1;

        typedef typename
            std::remove_cv<typename C1::mapped_type>::type no_cv_mapped_t1;
        typedef typename
            std::remove_reference<no_cv_mapped_t1>::type no_cvr_mapped_t1;


        typedef typename
            std::remove_cv<typename C2::key_type>::type no_cv_key_t2;
        typedef typename
            std::remove_reference<no_cv_key_t2>::type no_cvr_key_t2;

        typedef typename
            std::remove_cv<typename C2::mapped_type>::type no_cv_mapped_t2;
        typedef typename
            std::remove_reference<no_cv_mapped_t2>::type no_cvr_mapped_t2;


        bool is_same_key = std::is_same<no_cvr_key_t1, no_cvr_key_t2>::value;
        bool is_same_mapped =
            std::is_same<no_cvr_mapped_t1, no_cvr_mapped_t2>::value;

        if (!is_same_key || !is_same_mapped)
            return true;

        for (auto it = c2.begin(); it != c2.end(); it++) {
            c1->insert(*it);
        }

        return false;
    }
};

template<>
struct Merge<set_tag, set_tag> {
    template<class C1, class C2>
    static bool merge(C1* c1, const C2& c2) {
        typedef typename
            std::remove_cv<typename C1::value_type>::type no_cv_value_t1;
        typedef typename
            std::remove_reference<no_cv_value_t1>::type no_cvr_value_t1;

        typedef typename
            std::remove_cv<typename C2::value_type>::type no_cv_value_t2;
        typedef typename
            std::remove_reference<no_cv_value_t2>::type no_cvr_value_t2;

        if (std::is_same<no_cvr_value_t1, no_cvr_value_t2>::value == false)
            return true;

        for (auto it = c2.begin(); it != c2.end(); it++) {
            c1->insert(*it);
        }

        return false;
    }
};

template<class C1, class C2>
bool MergeAssociative(C1* c1, const C2& c2) {
    auto t1 = ContainerType<C1>::type_id;
    auto t2 = ContainerType<C2>::type_id;
    // map 1; mmap 2; umap 3; ummap 4;
    // set 10; mset 20; uset 30; umset 40;

    typedef typename ContainerType<C1>::tag tag1;
    typedef typename ContainerType<C2>::tag tag2;

    if (t1 * t2 == 0 ||
        (t1 < 10 && t2 >= 10) ||
        (t1 >= 10 && t2 < 10) ||
        ((t2 == 2 || t2 == 4) && (t1 == 1 || t1 == 3)) ||
        ((t2 == 20 || t2 == 40) && (t1 == 10 || t1 == 30)))
        return true;

    return Merge<tag1, tag2>::merge(c1, c2);
}
