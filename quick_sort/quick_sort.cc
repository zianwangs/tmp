#include <bits/stdc++.h>

using namespace std;

template <int... nums>
struct seq {
    static vector<int> toArray() { return {nums...}; }
};

template <typename T, typename U>
struct merge;

template <int... nums1, int... nums2>
struct merge<seq<nums1...>, seq<nums2...>> {
    using type = seq<nums1..., nums2...>;
};

template<typename T, typename L, typename R, int>
struct partition;

template<int head, int... tail, int... first, int... second, int pivot>
struct partition<seq<head, tail...>, seq<first...>, seq<second...>, pivot> {
    using type = typename conditional<(head < pivot), typename partition<seq<tail...>, seq<head, first...>, seq<second...>, pivot>::type, typename partition<seq<tail...>, seq<first...>, seq<head, second...>, pivot>::type>::type;
};

template<int head1, int... tail1, int head2, int... tail2, int pivot>
struct partition<seq<>, seq<head1, tail1...>, seq<head2, tail2...>, pivot> {
    using left  = typename partition<seq<tail1...>, seq<>, seq<>, head1>::type;
    using right = typename partition<seq<tail2...>, seq<>, seq<>, head2>::type;
    using type  = typename merge<typename merge<left, seq<pivot>>::type, right>::type;
};

template<int head, int... tail, int pivot>
struct partition<seq<>, seq<head, tail...>, seq<>, pivot> {
    using left = typename partition<seq<tail...>, seq<>, seq<>, head>::type;
    using type = typename merge<left, seq<pivot>>::type; 
};

template<int head, int... tail, int pivot>
struct partition<seq<>, seq<>, seq<head, tail...>, pivot> {
    using right = typename partition<seq<tail...>, seq<>, seq<>, head>::type;
    using type = typename merge<seq<pivot>, right>::type; 
};

template<int pivot>
struct partition<seq<>, seq<>, seq<>, pivot> {
    using type = seq<pivot>;
};

template<typename T>
struct quick_sort;

template<int head, int... tail>
struct quick_sort<seq<head, tail...>> {
    using type = typename partition<seq<tail...>, seq<>, seq<>, head>::type;
};



using l = seq<4,5,2,6,3,5,1>;
using sorted = typename quick_sort<l>::type;

int main() {
    for (int i : sorted::toArray())
        cout << i << ", ";
}
