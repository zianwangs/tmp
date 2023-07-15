using stk = Stack<int>;
static_assert(size<stk>::value == 0);
using stk1 = push<stk, 1>;
using stk2 = push<stk1, 2>;
static_assert(size<stk2>::value == 2);
static_assert(top<stk2>::value == 2);
using stk3 = pop<stk2>;
static_assert(size<stk3>::value == 1);
static_assert(top<stk3>::value == 1);
static_assert(size<pop<stk3>>::value == 0);