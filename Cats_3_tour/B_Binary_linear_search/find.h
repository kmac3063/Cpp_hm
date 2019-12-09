#pragma once

template<typename T, typename Iterator, typename type> struct F;

template<typename T, typename Iterator>
struct F <T, Iterator, std::random_access_iterator_tag> {
    static Iterator find(const T& value, Iterator first, Iterator last) {
        size_t size = last - first;
        size_t l = 0, r = size - 1, m;
        while (l < r) {
            m = (l + r) / 2;

            if (*(first + m) < value)
                l = m + 1;
            else
                r = m;
        }

        return *(first + l) == value ? first + l : last;
    }
};

template<typename T, typename Iterator, typename type>
struct F {
    static Iterator find(const T& value, Iterator first, Iterator last) {
        for (auto it = first; it != last; it++) {
            if (*it == value)
                return it;
        }
        return last;
    }
};


template<typename T, typename Iterator>
Iterator Find(const T& value, Iterator first, Iterator last) {
    typedef typename std::iterator_traits<Iterator>::iterator_category it_cat;
    return F<T, Iterator, it_cat>::find(value, first, last);
}
