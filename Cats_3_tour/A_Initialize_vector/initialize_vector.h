#pragma once

#include <vector>

template<typename T>
static T get(T value) {
    return value;
}

template <typename T, typename Head, typename... Tail>
static auto get(T value, Head head, Tail... tail) {
    auto rec = get(value, tail...);
    return std::vector< decltype(rec) >(head, rec);
}

template <typename T, typename... Args>
auto initialize_vector(T value, Args... args) {
    return get(value, args...);
}
