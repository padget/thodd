#include <iostream>
#include <exception>

#include <thodd/meta/traits/is_arithmetic.hpp>
#include <thodd/meta/traits/is_array.hpp>
#include <thodd/meta/traits/is_base_of.hpp>
#include <thodd/meta/traits/is_class.hpp>
#include <thodd/meta/traits/is_compound.hpp>
#include <thodd/meta/traits/is_empty.hpp>
#include <thodd/meta/traits/is_enum.hpp>
#include <thodd/meta/traits/is_floating_point.hpp>
#include <thodd/meta/traits/is_function.hpp>
#include <thodd/meta/traits/is_fundamental.hpp>
#include <thodd/meta/traits/is_integral.hpp>
#include <thodd/meta/traits/is_lvalue_reference.hpp>
#include <thodd/meta/traits/is_rvalue_reference.hpp>
#include <thodd/meta/traits/is_member_function_pointer.hpp>
#include <thodd/meta/traits/is_member_object_pointer.hpp>
#include <thodd/meta/traits/is_member_pointer.hpp>
#include <thodd/meta/traits/is_nullptr.hpp>
#include <thodd/meta/traits/is_object.hpp>
#include <thodd/meta/traits/is_pointer.hpp>
#include <thodd/meta/traits/is_reference.hpp>
//#include <thodd/meta/traits/is_same.hpp>
#include <thodd/meta/traits/is_scalar.hpp>
#include <thodd/meta/traits/is_union.hpp>
#include <thodd/meta/traits/is_void.hpp>

#include <thodd/meta/traits/decay.hpp>


#include <thodd/meta/pack/transfer.hpp>
#include <thodd/meta/pack/contains.hpp>
#include <thodd/meta/pack/concat.hpp>
#include <thodd/meta/pack/unique.hpp>
#include <thodd/meta/utils/if.hpp>

#include <thodd/meta/traits/concepts.hpp>

using namespace thodd::meta;


static_assert(is_array(type_<int[]>{}));
static_assert(!is_array(type_<int>{}));

struct base{};
struct derived : public base{};

static_assert(is_base_of(type_<base>{}, type_<derived>{}));
static_assert(!is_base_of(type_<derived>{}, type_<base>{}));

static_assert(is_class(type_<base>{}));
static_assert(!is_class(type_<int>{}));

struct not_empty
{
    int i;
};

static_assert(is_empty(type_<base>{}));
static_assert(!is_empty(type_<not_empty>{}));

enum class day
{
    MONDAY, 
    SUNDAY
};

static_assert(is_enum(type_<day>{}));
static_assert(!is_enum(type_<base>{}));

static_assert(is_floating_point(type_<double>{}));
static_assert(!is_floating_point(type_<int>{}));

static_assert(is_integral(type_<int>{}));
static_assert(!is_integral(type_<double>{}));

static_assert(is_lvalue_reference(type_<int&>{}));
static_assert(!is_lvalue_reference(type_<double>{}));

static_assert(!is_rvalue_reference(type_<int>{}));
static_assert(is_rvalue_reference(type_<double&&>{}));

static_assert(is_nullptr(type_<std::nullptr_t>{}));
static_assert(!is_nullptr(type_<int>{}));

static_assert(is_pointer(type_<int*>{}));
static_assert(!is_pointer(type_<int>{}));

static_assert(is_same(decay(type_<int const &&>{}), type_<int>{}));


template<typename...> struct pack1{};
template<typename...> struct pack2{};

static_assert(is_same(type_<decltype(transfer<pack2>(pack1<int, short>{}))>{}, type_<pack2<int, short>>{}));
static_assert(contains(pack1<int, short, double>{}, type_<double>{}));
static_assert(is_same(if_<true>(type_<int>{}, type_<short>{}), type_<int>{}));
static_assert(is_same(type_<decltype(concat(pack1<int>{}, pack1<short>{}, pack2<double>{}))>{}, type_<pack1<int, short, double>>{}));
static_assert(is_same(type_<decltype(unique(pack1<int, int, short>{}))>{}, type_<pack1<int, short>>{}));


main() {}
