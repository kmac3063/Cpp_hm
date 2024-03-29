#pragma once

#include <functional>
#include <memory>
#include <utility>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <cmath>

namespace fefu
{
    #define EMPTY 0
    #define USE 1
    #define DEL 2
    
    template<typename T>
    class allocator {
    public:
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = typename std::add_lvalue_reference<T>::type;
        using const_reference = typename std::add_lvalue_reference<const T>::type;
        using value_type = T;

        allocator() noexcept = default;

        allocator(const allocator&) noexcept = default;

        template <class U>
        allocator(const allocator<U>&) noexcept {};

        ~allocator() = default;

        pointer allocate(size_type size) {
            return static_cast<pointer>(::operator new(size * sizeof(value_type)));
        }

        void deallocate(pointer p, size_type n) noexcept {
            ::operator delete(p, n);
        }

        void setSeed(const int& s) {
            seed = s;
        }

        int getSeed() {
            return seed;
        }
    private:
        int seed = 0;
    };

    template<typename K, typename T,
        typename Hash,
        typename Pred,
        typename Alloc>
        class hash_map;

    template<typename ValueType>
    class hash_map_const_iterator;

    template<typename ValueType>
    class hash_map_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ValueType;
        using difference_type = std::ptrdiff_t;
        using reference = ValueType&;
        using pointer = ValueType*;

        hash_map_iterator() noexcept = default;
        hash_map_iterator(const hash_map_iterator& other) noexcept : 
            p(other.p), 
            s(other.s),
            i(other.i) {}

        reference operator*() const {
            return *p;
        }
        pointer operator->() const {
            return p;
        }

        // prefix ++
        hash_map_iterator& operator++() {
            if (i >= s->size())
                throw;

            i++;
            p++;
            while (i < s->size() && (*s)[i] != USE) {
                i++;
                p++;
            }

            return *this;
        }
        // postfix ++
        hash_map_iterator operator++(int) {
            hash_map_iterator t(*this);

            if (i >= s->size())
                throw;

            i++;
            p++;
            while (i < s->size() && (*s)[i] != USE) {
                i++;
                p++;
            }

            return t;
        }

        friend bool operator==(const hash_map_iterator<ValueType>& a, const hash_map_iterator<ValueType>& b) {
            return &*a == &*b;
        }

        friend bool operator!=(const hash_map_iterator<ValueType>& a, const hash_map_iterator<ValueType>& b) {
            return &*a != &*b;
        }

        template<typename ValueType>
        friend class hash_map_const_iterator;

        template<typename K, typename T,
            typename Hash,
            typename Pred,
            typename Alloc>
            friend class hash_map;
    private:
        hash_map_iterator(pointer p_, std::vector<char>* s_, size_t i_) noexcept : 
            i(i_),
            p(p_ + i_),
            s(s_) {}

        size_t i = 0;
        pointer p = 0;
        std::vector<char>* s;
    };

    template<typename ValueType>
    class hash_map_const_iterator {
        // Shouldn't give non const references on value
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ValueType;
        using difference_type = std::ptrdiff_t;
        using reference = const ValueType&;
        using pointer = const ValueType*;

        hash_map_const_iterator() noexcept {};
        hash_map_const_iterator(const hash_map_const_iterator& other) noexcept : 
            p(other.p), 
            s(other.s), 
            i(other.i) {};
        hash_map_const_iterator(const hash_map_iterator<ValueType>& other) noexcept :
            p(other.p),
            s(other.s),
            i(other.i) {};

        reference operator*() const {
            return *p;
        }
        pointer operator->() const {
            return p;
        }

        // prefix ++
        hash_map_const_iterator& operator++() {
            if (i >= s->size())
                throw;

            i++;
            p++;
            while (i < s->size() && (*s)[i] != USE) {
                i++;
                p++;
            }

            return *this;
        }
        // postfix ++
        hash_map_const_iterator operator++(int) {
            hash_map_const_iterator t(*this);

            if (i >= s->size())
                throw;

            i++;
            p++;
            while (i < s->size() && (*s)[i] != USE) {
                i++;
                p++;
            }

            return t;
        }


        friend bool operator==(const hash_map_const_iterator<ValueType>& a, const hash_map_const_iterator<ValueType>& b) {
            return &*a == &*b;
        }
        friend bool operator!=(const hash_map_const_iterator<ValueType>& a, const hash_map_const_iterator<ValueType>& b) {
            return &*a != &*b;
        }

        template<typename K, typename T,
            typename Hash,
            typename Pred,
            typename Alloc>
            friend class hash_map;

    private:
        hash_map_const_iterator(pointer p_, const std::vector<char>* s_, const size_t i_) noexcept : 
            i(i_),
            p(p_ + i_),
            s(s_) {}

        size_t i = 0;
        pointer p = 0;
        const std::vector<char>* s;
    };

    template<typename K, typename T,
        typename Hash = std::hash<K>,
        typename Pred = std::equal_to<K>,
        typename Alloc = allocator<std::pair<const K, T>>>
        class hash_map {
        public:
            using key_type = K;
            using mapped_type = T;
            using hasher = Hash;
            using key_equal = Pred;
            using allocator_type = Alloc;
            using value_type = std::pair<const key_type, mapped_type>;
            using reference = value_type&;
            using const_reference = const value_type&;
            using iterator = hash_map_iterator<value_type>;
            using const_iterator = hash_map_const_iterator<value_type>;
            using size_type = std::size_t;

            const float BASE_LOAD_FACTOR = 0.5555555f;
            /// Default constructor.
            hash_map() = default;

            /**
             *  @brief  Default constructor creates no elements.
             *  @param n  Minimal initial number of buckets.
             */
            explicit hash_map(size_type n) :
                m_set(n, 0),
                m_data(m_allocator.allocate(n)) {}

            /**
             *  @brief  Builds an %hash_map from a range.
             *  @param  first  An input iterator.
             *  @param  last  An input iterator.
             *  @param  n  Minimal initial number of buckets.
             *
             *  Create an %hash_map consisting of copies of the elements from
             *  [first,last).  This is linear in N (where N is
             *  distance(first,last)).
             */
            template<typename InputIterator>
            hash_map(InputIterator first, InputIterator last,
                size_type n = 0) {
                if (n < 1)
                    n = 1;
                hash_map map(n);
                for (auto it = first; it != last; it++)
                    map.insert(*it);
                *this = map;
            }

            /// Copy constructor.
            hash_map(const hash_map& m) :
                m_set(m.m_set),
                m_allocator(m.get_allocator()),
                m_data(m_allocator.allocate(m.m_set.size())),
                m_hash(m.hash_function()),
                m_key_equal(m.key_eq()),
                use_size(m.size()) {

                max_load_factor(m.max_load_factor());
                memcpy(m_data, m.m_data, m.m_set.size() * sizeof(value_type));
            }
            /// Move constructor.
            hash_map(hash_map&& m) :
                m_set(std::move(m.m_set)),
                m_allocator(std::move(m.get_allocator())),
                m_data(m_allocator.allocate(m.m_set.size())),
                m_hash(std::move(m.hash_function())),
                m_key_equal(std::move(m.key_eq())),
                use_size(std::move(m.size())) {

                max_load_factor(std::move(m.max_load_factor()));
                memmove(m_data, m.m_data, m.m_set.size() * sizeof(value_type));
            }

            /**
             *  @brief Creates an %hash_map with no elements.
             *  @param a An allocator object.
             */
            explicit hash_map(const allocator_type& a) {
                m_allocator = a;
            }

            /*
            *  @brief Copy constructor with allocator argument.
            * @param  uset  Input %hash_map to copy.
            * @param  a  An allocator object.
            */
            hash_map(const hash_map& m,
                const allocator_type& a) :
                m_set(m.m_set),
                m_allocator(a),
                m_data(m_allocator.allocate(m.m_set.size())),
                m_hash(m.hash_function()),
                m_key_equal(m.key_eq()),
                use_size(m.size()) {

                max_load_factor(m.max_load_factor());
                memcpy(m_data, m.m_data, m.m_set.size() * sizeof(value_type));
            }
            /*
            *  @brief  Move constructor with allocator argument.
            *  @param  uset Input %hash_map to move.
            *  @param  a    An allocator object.
            */
            hash_map(hash_map&& m,
                const allocator_type& a) :

                m_set(std::move(m.m_set)),
                m_allocator(a),
                m_data(m_allocator.allocate(m.m_set.size())),
                m_hash(std::move(m.hash_function())),
                m_key_equal(std::move(m.key_eq())),
                use_size(std::move(m.size())) {

                max_load_factor(std::move(m.max_load_factor()));
                memmove(m_data, m.m_data, m.m_set.size() * sizeof(value_type));
            }
            /**
             *  @brief  Builds an %hash_map from an initializer_list.
             *  @param  l  An initializer_list.
             *  @param n  Minimal initial number of buckets.
             *
             *  Create an %hash_map consisting of copies of the elements in the
             *  list. This is linear in N (where N is @a l.size()).
             */
            hash_map(std::initializer_list<value_type> l,
                size_type n = 0) {
                if (n < 1)
                    n = 1;
                hash_map map(n);
                for (auto el : l)
                    map.insert(el);
                *this = map;
            }

            ~hash_map() {
                m_allocator.deallocate(m_data, m_set.size());
            }

            /// Copy assignment operator.
            hash_map& operator=(const hash_map& m) {
                m_allocator.deallocate(m_data, m_set.size());

                m_set = m.m_set;
                m_allocator = m.m_allocator;
                m_data = m_allocator.allocate(m.m_set.size());
                
                m_hash = m.hash_function();
                m_key_equal = m.key_eq();
                use_size = m.size();
                max_load_factor(m.max_load_factor());
                memcpy(m_data, m.m_data, m.m_set.size() * sizeof(value_type) );

                return *this;
            }

            /// Move assignment operator.
            hash_map& operator=(hash_map&& m) {
                m_allocator.deallocate(m_data, m_set.size());

                m_set = std::move(m.m_set);
                m_allocator = std::move(m.m_allocator);
                m_data = m_allocator.allocate(m.m_set.size());

                m_hash = std::move(m.hash_function());
                m_key_equal = std::move(m.key_eq());
                use_size = m.size();
                max_load_factor(m.max_load_factor());

                memmove(m_data, m.m_data, m.m_set.size() * sizeof(value_type));
                return *this;
            }

            /**
             *  @brief  %hash_map list assignment operator.
             *  @param  l  An initializer_list.
             *
             *  This function fills an %hash_map with copies of the elements in
             *  the initializer list @a l.
             *
             *  Note that the assignment completely changes the %hash_map and
             *  that the resulting %hash_map's size is the same as the number
             *  of elements assigned.
             */
            hash_map& operator=(std::initializer_list<value_type> l) {
                hash_map map(l.size());
                for (auto el : l)
                    map.insert(el);
                return *this = map;
            }

            ///  Returns the allocator object used by the %hash_map.
            allocator_type get_allocator() const noexcept {
                return m_allocator;
            }

            // size and capacity:

            ///  Returns true if the %hash_map is empty.
            bool empty() const noexcept {
                return use_size == 0;
            }

            ///  Returns the size of the %hash_map.
            size_type size() const noexcept {
                return use_size;
            }

            ///  Returns the maximum size of the %hash_map.
            size_type max_size() const noexcept {
                return UINT32_MAX;
            }

            // iterators.

            /**
             *  Returns a read/write iterator that points to the first element in the
             *  %hash_map.
             */
            iterator begin() noexcept {
                size_type i = 0;
                while (i < m_set.size() && m_set[i] != USE)
                    i++;

                return iterator(m_data, &m_set, i);
            };


            //@{
            /**
             *  Returns a read-only (constant) iterator that points to the first
             *  element in the %hash_map.
             */
            const_iterator begin() const noexcept {
                size_type i = 0;
                while (i < m_set.size() && m_set[i] != USE)
                    i++;

                return const_iterator(m_data, &m_set, i);
            }

            const_iterator cbegin() const noexcept {
                size_type i = 0;
                while (i < m_set.size() && m_set[i] != USE)
                    i++;

                return const_iterator(m_data, &m_set, i);
            }

            /**
             *  Returns a read/write iterator that points one past the last element in
             *  the %hash_map.
             */
            iterator end() noexcept {
                return iterator(m_data, &m_set, m_set.size());
            }

            //@{
            /**
             *  Returns a read-only (constant) iterator that points one past the last
             *  element in the %hash_map.
             */
            const_iterator end() const noexcept {
                return const_iterator(m_data, &m_set, m_set.size());
            }

            const_iterator cend() const noexcept {
                return const_iterator(m_data, &m_set, m_set.size());
            }
            //@}

            // modifiers.

            /**
             *  @brief Attempts to build and insert a std::pair into the
             *  %hash_map.
             *
             *  @param args  Arguments used to generate a new pair instance (see
             *	        std::piecewise_contruct for passing arguments to each
            *	        part of the pair constructor).
            *
            *  @return  A pair, of which the first element is an iterator that points
            *           to the possibly inserted pair, and the second is a bool that
            *           is true if the pair was actually inserted.
            *
            *  This function attempts to build and insert a (key, value) %pair into
            *  the %hash_map.
            *  An %hash_map relies on unique keys and thus a %pair is only
            *  inserted if its first element (the key) is not already present in the
            *  %hash_map.
            *
            *  Insertion requires amortized constant time. 
            */
            template<typename... _Args>
            std::pair<iterator, bool> emplace(_Args&&... args);

            /**
             *  @brief Attempts to build and insert a std::pair into the
             *  %hash_map.
             *
             *  @param k    Key to use for finding a possibly existing pair in
             *                the hash_map.
             *  @param args  Arguments used to generate the .second for a
             *                new pair instance.
             *
             *  @return  A pair, of which the first element is an iterator that points
             *           to the possibly inserted pair, and the second is a bool that
             *           is true if the pair was actually inserted.
             *
             *  This function attempts to build and insert a (key, value) %pair into
             *  the %hash_map.
             *  An %hash_map relies on unique keys and thus a %pair is only
             *  inserted if its first element (the key) is not already present in the
             *  %hash_map.
             *  If a %pair is not inserted, this function has no effect.
             *
             *  Insertion requires amortized constant time.
             */
            template <typename... _Args>
            std::pair<iterator, bool> try_emplace(const key_type& k, _Args&&... args);

            // move-capable overload
            template <typename... _Args>
            std::pair<iterator, bool> try_emplace(key_type&& k, _Args&&... args);

            //@{
            /**
            *  @brief Attempts to insert a std::pair into the %hash_map.
            *  @param x Pair to be inserted (see std::make_pair for easy
            *	     creation of pairs).
            *
            *  @return  A pair, of which the first element is an iterator that
            *           points to the possibly inserted pair, and the second is
            *           a bool that is true if the pair was actually inserted.
            *
            *  This function attempts to insert a (key, value) %pair into the
            *  %hash_map. An %hash_map relies on unique keys and thus a
            *  %pair is only inserted if its first element (the key) is not already
            *  present in the %hash_map.
            *
            *  Insertion requires amortized constant time.
            */
            std::pair<iterator, bool> insert(const value_type& x) {
                if (bucket_count() < 3)
                    rehash(3);
                size_type index = bucket(x.first);

                if (m_set[index] == USE) {
                    return std::make_pair(iterator(m_data, &m_set, index), false);
                }

                m_set[index] = USE;
                new(m_data + index) value_type{ x.first, x.second };
                use_size++;

                if (load_factor() > max_load_factor()) {
                    rehash(next_prime(3 * bucket_count() / 2));
                    index = bucket(x.first);
                }
                
                return std::make_pair(iterator(m_data, &m_set, index), true);
            }

            std::pair<iterator, bool> insert(value_type&& x) {
                if (bucket_count() < 3)
                    rehash(3);
                size_type index = bucket(x.first);

                if (m_set[index] == USE) {
                    return std::make_pair(iterator(m_data, &m_set, index), false);
                }

                m_set[index] = USE;
                new(m_data + index) value_type{ x.first, x.second };
                use_size++;

                if (load_factor() > max_load_factor()) {
                    rehash(next_prime(3 * bucket_count() / 2));
                    index = bucket(x.first);
                }

                return std::make_pair(iterator(m_data, &m_set, index), true);
            }

            //@}

            /**
             *  @brief A template function that attempts to insert a range of
             *  elements.
             *  @param  first  Iterator pointing to the start of the range to be
             *                   inserted.
             *  @param  last  Iterator pointing to the end of the range.
             *
             *  Complexity similar to that of the range constructor.
             */
            template<typename _InputIterator>
            void insert(_InputIterator first, _InputIterator last) {
                for (auto it = first; it != last; it++) {
                    insert(*it);
                }
            }

            /**
             *  @brief Attempts to insert a list of elements into the %hash_map.
             *  @param  l  A std::initializer_list<value_type> of elements
             *               to be inserted.
             *
             *  Complexity similar to that of the range constructor.
             */
            void insert(std::initializer_list<value_type> l) {
                for (auto it = l.begin(); it != l.end(); it++){
                    insert(*it);
                }
            }


            /**
             *  @brief Attempts to insert a std::pair into the %hash_map.
             *  @param k    Key to use for finding a possibly existing pair in
             *                the map.
             *  @param obj  Argument used to generate the .second for a pair
             *                instance.
             *
             *  @return  A pair, of which the first element is an iterator that
             *           points to the possibly inserted pair, and the second is
             *           a bool that is true if the pair was actually inserted.
             *
             *  This function attempts to insert a (key, value) %pair into the
             *  %hash_map. An %hash_map relies on unique keys and thus a
             *  %pair is only inserted if its first element (the key) is not already
             *  present in the %hash_map.
             *  If the %pair was already in the %hash_map, the .second of
             *  the %pair is assigned from obj.
             *
             *  Insertion requires amortized constant time.
             */
            template <typename _Obj>
            std::pair<iterator, bool> insert_or_assign(const key_type& k, _Obj&& obj) {
                if (bucket_count() < 3)
                    rehash(3);
                size_type index = bucket(k);

                bool ans = true;

                if (m_set[index] == USE) {
                    ans = false;
                    m_data[index].~value_type();
                    use_size--;
                }

                m_set[index] = USE;
                new(m_data + index) value_type{ k, obj };
                use_size++;

                if (load_factor() > max_load_factor()) {
                    rehash(next_prime(3 * bucket_count() / 2));
                    index = bucket(k);
                }

                return std::make_pair(iterator(m_data, &m_set, index), ans);
            }

            // move-capable overload
            template <typename _Obj>
            std::pair<iterator, bool> insert_or_assign(key_type&& k, _Obj&& obj) {
                if (bucket_count() < 3)
                    rehash(3);
                size_type index = bucket(k);

                bool ans = true;

                if (m_set[index] == USE) {
                    ans = false;
                    m_data[index].~value_type();
                    use_size--;
                }

                m_set[index] = USE;
                new(m_data + index) value_type{ k, std::move(obj) };
                use_size++;

                if (load_factor() > max_load_factor()) {
                    rehash(next_prime(3 * bucket_count() / 2));
                    index = bucket(k);
                }

                return std::make_pair(iterator(m_data, &m_set, index), ans);
            }

            //@{
            /**
             *  @brief Erases an element from an %hash_map.
             *  @param  position  An iterator pointing to the element to be erased.
             *  @return An iterator pointing to the element immediately following
             *          @a position prior to the element being erased. If no such
             *          element exists, end() is returned.
             *
             *  This function erases an element, pointed to by the given iterator,
             *  from an %hash_map.
             *  Note that this function only erases the element, and that if the
             *  element is itself a pointer, the pointed-to memory is not touched in
             *  any way.  Managing the pointer is the user's responsibility.
             */
            iterator erase(const_iterator position) {
                if (erase(position->first) == 1) {
                    if (++position == end())
                        return end();
                    return iterator(m_data, &m_set, position.i);
                }
                return end();
            }

            // LWG 2059.
            iterator erase(iterator position) {
                if (erase(position->first) == 1)
                    return ++position;
                return end();
            }
            //@}

            /**
             *  @brief Erases elements according to the provided key.
             *  @param  x  Key of element to be erased.
             *  @return  The number of elements erased.
             *
             *  This function erases all the elements located by the given key from
             *  an %hash_map. For an %hash_map the result of this function
             *  can only be 0 (not present) or 1 (present).
             *  Note that this function only erases the element, and that if the
             *  element is itself a pointer, the pointed-to memory is not touched in
             *  any way.  Managing the pointer is the user's responsibility.
             */
            size_type erase(const key_type& x) {
                size_type index = bucket(x);

                if (m_set[index] != USE)
                    return 0;
                
                m_set[index] = DEL;
                use_size--;
                
                return 1;
            }

            /**
             *  @brief Erases a [first,last) range of elements from an
             *  %hash_map.
             *  @param  first  Iterator pointing to the start of the range to be
             *                  erased.
             *  @param last  Iterator pointing to the end of the range to
             *                be erased.
             *  @return The iterator @a last.
             *
             *  This function erases a sequence of elements from an %hash_map.
             *  Note that this function only erases the elements, and that if
             *  the element is itself a pointer, the pointed-to memory is not touched
             *  in any way.  Managing the pointer is the user's responsibility.
             */
            iterator erase(const_iterator first, const_iterator last) {
                auto tlast = first;
                for (auto it = first; it != last; it++) {
                    if (erase(it->first) == 1)
                        tlast = it;
                }

                if (++tlast == end())
                    return end();
                return iterator(m_data, &m_set, tlast.i);
            }

            /**
             *  Erases all elements in an %hash_map.
             *  Note that this function only erases the elements, and that if the
             *  elements themselves are pointers, the pointed-to memory is not touched
             *  in any way.  Managing the pointer is the user's responsibility.
             */
            void clear() noexcept {
                m_allocator.deallocate(m_data, m_set.size());
                m_data = m_allocator.allocate(m_set.size());
                use_size = 0;
                m_set.clear();
            }

            /**
             *  @brief  Swaps data with another %hash_map.
             *  @param  x  An %hash_map of the same element and allocator
             *  types.
             *
             *  This exchanges the elements between two %hash_map in constant
             *  time.
             *  Note that the global std::swap() function is specialized such that
             *  std::swap(m1,m2) will feed to this function.
             */
            void swap(hash_map& x) {
                hash_map temp_map(*this);
                *this = x;
                x = temp_map;
            }

            template<typename _H2, typename _P2>
            void merge(hash_map<K, T, _H2, _P2, Alloc>& source);

            template<typename _H2, typename _P2>
            void merge(hash_map<K, T, _H2, _P2, Alloc>&& source);

            // observers.

            ///  Returns the hash functor object with which the %hash_map was
            ///  constructed.
            Hash hash_function() const {
                return m_hash;
            }

            ///  Returns the key comparison object with which the %hash_map was
            ///  constructed.
            Pred key_eq() const {
                return m_key_equal;
            }

            // lookup.

            //@{
            /**
             *  @brief Tries to locate an element in an %hash_map.
             *  @param  x  Key to be located.
             *  @return  Iterator pointing to sought-after element, or end() if not
             *           found.
             *
             *  This function takes a key and tries to locate the element with which
             *  the key matches.  If successful the function returns an iterator
             *  pointing to the sought after element.  If unsuccessful it returns the
             *  past-the-end ( @c end() ) iterator.
             */
            iterator find(const key_type& x) {
                size_type index = bucket(x);
                
                if (m_set[index] != USE)
                    return end();

                return iterator(m_data, &m_set, index);
            }

            const_iterator find(const key_type& x) const {
                size_type index = bucket(x);

                if (m_set[index] != USE)
                    return end();
                
                return const_iterator(m_data, &m_set, index);
            }
            //@}

            /**
             *  @brief  Finds the number of elements.
             *  @param  x  Key to count.
             *  @return  Number of elements with specified key.
             *
             *  This function only makes sense for %unordered_multimap; for
             *  %hash_map the result will either be 0 (not present) or 1
             *  (present).
             */
            size_type count(const key_type& x) const {
                return (m_set[bucket(x)] == USE);
            }

            /**
             *  @brief  Finds whether an element with the given key exists.
             *  @param  x  Key of elements to be located.
             *  @return  True if there is any element with the specified key.
             */
            bool contains(const key_type& x) const {
                return (m_set[bucket(x)] == USE);
            }

            //@{
            /**
             *  @brief  Subscript ( @c [] ) access to %hash_map data.
             *  @param  k  The key for which data should be retrieved.
             *  @return  A reference to the data of the (key,data) %pair.
             *
             *  Allows for easy lookup with the subscript ( @c [] )operator.  Returns
             *  data associated with the key specified in subscript.  If the key does
             *  not exist, a pair with that key is created using default values, which
             *  is then returned.
             *
             *  Lookup requires constant time.
             */
            mapped_type& operator[](const key_type& k) {
                size_type index = bucket(k);

                if (m_set[index] != USE) {
                    if (m_set[index] == DEL) {
                        m_data[index].~value_type();
                    }
                    use_size++;
                    m_set[index] = USE;

                    new(m_data + index) value_type{ k, mapped_type{} };

                    if (load_factor() > max_load_factor()) {
                        rehash(next_prime(3 * bucket_count() / 2));
                        index = bucket(k);
                    }
                }

                return (m_data + index)->second;
            }

            mapped_type& operator[](key_type&& k) {
                size_type index = bucket(k);

                if (m_set[index] != USE) {
                    if (m_set[index] == DEL) {
                        m_data[index].~value_type();
                    }
                    use_size++;
                    m_set[index] = USE;

                    new(m_data + index) value_type{ std::move(k), mapped_type{} };

                    if (load_factor() > max_load_factor()) {
                        rehash(next_prime(3 * bucket_count() / 2));
                        index = bucket(k);
                    }
                }

                return (m_data + index)->second;
            }
            //@}

            //@{
            /**
             *  @brief  Access to %hash_map data.
             *  @param  k  The key for which data should be retrieved.
             *  @return  A reference to the data whose key is equal to @a k, if
             *           such a data is present in the %hash_map.
             *  @throw  std::out_of_range  If no such data is present.
             */
            mapped_type& at(const key_type& k) {
                size_type index = bucket(k);

                if (m_set[index] != USE)
                    throw std::out_of_range("Error: index out of range!");
                
                return m_data[index].second;    
            }

            const mapped_type& at(const key_type& k) const {
                size_type index = bucket(k);

                if (m_set[index] != USE)
                    throw std::out_of_range("Error: index out of range!");

                const mapped_type& t = m_data[index].second;
                return t;
            }
            //@}

            // bucket interface.

            /// Returns the number of buckets of the %hash_map.
            size_type bucket_count() const noexcept {
                return m_set.size();
            }

            /*
            * @brief  Returns the bucket index of a given element.
            * @param  _K  A key instance.
            * @return  The key bucket index.
            */
            size_type bucket(const key_type& _K) const {
                size_type h1 = m_hash(_K) % m_set.size();
                size_type h2 = m_hash(_K) % (m_set.size() - 1) + 1;

                size_type first_del = -1;

                size_type i = 0;
                while (i < m_set.size()) {
                    if (first_del == -1 && m_set[h1] == DEL)
                        first_del = h1;

                    if (m_set[h1] == EMPTY)
                        break;

                    if (m_set[h1] == USE && m_data[h1].first == _K)
                        return h1;

                    h1 = (h1 + h2) % m_set.size();
                    i++;
                }
                
                if (first_del == -1)
                    return h1;
                return first_del;
            }

            // hash policy.

            /// Returns the average number of elements per bucket.
            float load_factor() const noexcept {
                return static_cast<float>(use_size) / m_set.size();
            }

            /// Returns a positive number that the %hash_map tries to keep the
            /// load factor less than or equal to.
            float max_load_factor() const noexcept {
                return max_load_factor_;
            }

            /**
             *  @brief  Change the %hash_map maximum load factor.
             *  @param  z The new maximum load factor.
             */
            void max_load_factor(float z) {
                max_load_factor_ = z;
            }

            /**
             *  @brief  May rehash the %hash_map.
             *  @param  n The new number of buckets.
             *
             *  Rehash will occur only if the new number of buckets respect the
             *  %hash_map maximum load factor.
             */
            void rehash(size_type n) {
                auto new_load_factor = static_cast<float>(use_size) / n;
                if (new_load_factor > max_load_factor())
                    return;

                if (!is_prime(n))
                    n = next_prime(n);

                hash_map hash_m(n);
                hash_m.m_allocator = m_allocator;
                hash_m.m_hash = m_hash;
                hash_m.m_key_equal = m_key_equal;

                for (auto it = begin(); it != end(); it++) {
                    hash_m.insert(*it);
                }

                *this = hash_m;
            }

            /**
             *  @brief  Prepare the %hash_map for a specified number of
             *          elements.
             *  @param  n Number of elements required.
             *
             *  Same as rehash(ceil(n / max_load_factor())).
             */
            void reserve(size_type n) {
                rehash(n / max_load_factor_);
            }

            bool operator==(const hash_map& other) const {
                for (auto it = begin(); it != end(); it++) {
                    if (!other.contains(it->first))
                        return false;
                }

                return size() == other.size();
            }

        private:
            bool is_prime(const size_type& n1) {
                for (size_type i = 2; i * i <= n1; i++)
                    if (n1 % i == 0)
                        return false;
                return true;
            }

            size_type next_prime(size_type n) {
                while (!is_prime(n)) {
                    n++;
                }
                return n;
            }

            allocator_type m_allocator;
            hasher m_hash;
            key_equal m_key_equal;

            std::vector<char> m_set;
            value_type* m_data = 0;
            size_type use_size = 0;
            float max_load_factor_ = BASE_LOAD_FACTOR;
    };

} // namespace fefu