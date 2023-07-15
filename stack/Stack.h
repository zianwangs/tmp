#include <type_traits>
#include <cstdlib>

struct _NIL {
	/* private */
	using _next = _NIL;
};

template <size_t _N>
struct _IntegerWrapper {
	/* public */
	static constexpr size_t value = _N;
};

template <typename _DataType, typename _Data = _NIL>
struct Stack {
	/* public */
	using empty = Stack<_DataType>;
	/* private */
	using _dataType = _DataType;
	using _data = _Data;
};

template <typename _DataType, _DataType _Value, typename _Next>
struct _Node {
	/* public */
	static constexpr _DataType value = _Value;
	/* private */
	using _dataType = _DataType;
	using _next = _Next;
};

template <typename _Stack, typename _Stack::_dataType _Item>
using push = Stack<typename _Stack::_dataType, _Node<typename _Stack::_dataType, _Item, typename _Stack::_data>>;

template <typename _Stack>
using pop = Stack<typename _Stack::_dataType, typename _Stack::_data::_next>;

template <typename _Stack>
using top = typename _Stack::_data;

template <typename _Node, size_t _N>
struct _SizeHelper {
	/* public */
	static constexpr size_t value = std::conditional<std::is_same<_Node, _NIL>::value, _IntegerWrapper<_N>, _SizeHelper<typename _Node::_next, _N + 1>>::type::value;
};

template <typename _Stack>
using size = _SizeHelper<typename _Stack::_data, 0>;

