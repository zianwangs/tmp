#include <bits/stdc++.h>
using namespace std;

struct NIL;

template <int n, typename L, typename R>
struct Node {
    static constexpr int val = n;
    using left = L;
    using right = R;
};

template<typename T = void>
struct BST {
    using create = BST<NIL>;
    using type = T;
};


template <typename T, int n>
struct insert;

template <int n> 
struct insert<BST<NIL>, n> {
    using type = BST<Node<n, NIL, NIL>>;
};

template <int r, typename L, typename R, int n>
struct insert<BST<Node<r, L, R>>, n> {
    using left = typename conditional<(r <= n), L, typename insert<BST<L>, n>::type::type>::type;
    using right = typename conditional<(r >= n), R, typename insert<BST<R>, n>::type::type>::type;
    using type = BST<Node<r, left, right>>;
};

template <typename T, int>
struct contains;

template <int n>
struct contains<BST<NIL>, n> {
    static constexpr bool value = false;
};

template <int r, typename T, typename U>
struct contains<BST<Node<r, T, U>>, r> {
    static constexpr bool value = true;
};

template <int r, typename T, typename U, int n>
struct contains<BST<Node<r, T, U>>, n> {
    static constexpr bool value = conditional<(r > n), contains<BST<typename Node<r, T, U>::left>, n>, contains<BST<typename Node<r, T, U>::right>, n>>::type::value;
};


template <typename T, typename U>
struct merge;

template <typename T>
struct merge<BST<NIL>, BST<T>> {
    using type = BST<T>;
};

template <typename T>
struct merge<BST<T>, BST<NIL>> {
    using type = BST<T>;
};

template <int v1, typename L1, typename R1, int v2, typename L2, typename R2>
struct merge<BST<Node<v1, L1, R1>>, BST<Node<v2, L2, R2>>> {
    using left = typename conditional<(v1 < v2), L1, typename merge<BST<L1>, BST<Node<v2, L2, R2>>>::type::type>::type;
    using right = typename conditional<(v1 > v2), R1, typename merge<BST<R1>, BST<Node<v2, L2, R2>>>::type::type>::type;
    using type = BST<Node<v1, left, right>>;
};

template <typename T, int>
struct erase;

template <int n> 
struct erase<BST<NIL>, n> {
    using type = BST<NIL>;
};

template <int r, typename L, typename R>
struct erase<BST<Node<r, L, R>>, r> {
    using type = typename merge<BST<L>,BST<R>>::type;
};

template <int r, typename L, typename R, int n>
struct erase<BST<Node<r, L, R>>, n> {
    using left = typename conditional<(r < n), L, typename erase<BST<L>, n>::type::type>::type;
    using right = typename conditional<(r > n), R, typename erase<BST<R>, n>::type::type>::type;
    using type = BST<Node<r, left, right>>;
};


using tree = BST<>::create;
static_assert(contains<tree, 3>::value == false);
using tree1 = insert<tree, 1>::type;
static_assert(contains<tree1, 3>::value == false);
using tree2 = insert<tree1, 3>::type;
static_assert(contains<tree2, 3>::value);
using tree3 = insert<tree2, 2>::type;
using tree4 = insert<tree3, 4>::type;
static_assert(is_same<tree4, BST<Node<1, NIL, Node<3, Node<2, NIL, NIL>, Node<4, NIL, NIL>>>>>::value);
using tree5 = erase<tree4, 3>::type;
static_assert(is_same<tree5, BST<Node<1, NIL, Node<2, NIL, Node<4, NIL, NIL>>>>>::value);

