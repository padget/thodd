#include <iostream>
#include <exception>

#include <thodd/meta/traits/is_arithmetic.hpp>
#include <thodd/meta/traits/is_array.hpp>
#include <thodd/meta/traits/is_base_of.hpp>
#include <thodd/meta/traits/is_class.hpp>
// #include <thodd/meta/traits/is_compound.hpp>
#include <thodd/meta/traits/is_empty.hpp>
#include <thodd/meta/traits/is_enum.hpp>
#include <thodd/meta/traits/is_floating_point.hpp>
// #include <thodd/meta/traits/is_function.hpp>
// #include <thodd/meta/traits/is_fundamental.hpp>
#include <thodd/meta/traits/is_integral.hpp>
#include <thodd/meta/traits/is_lvalue_reference.hpp>
#include <thodd/meta/traits/is_rvalue_reference.hpp>
// #include <thodd/meta/traits/is_member_function_pointer.hpp>
// #include <thodd/meta/traits/is_member_object_pointer.hpp>
// #include <thodd/meta/traits/is_member_pointer.hpp>
#include <thodd/meta/traits/is_nullptr.hpp>
// #include <thodd/meta/traits/is_object.hpp>
#include <thodd/meta/traits/is_pointer.hpp>
#include <thodd/meta/traits/is_reference.hpp>
#include <thodd/meta/traits/is_same.hpp>
#include <thodd/meta/traits/is_scalar.hpp>
#include <thodd/meta/traits/is_union.hpp>
// #include <thodd/meta/traits/is_void.hpp>

using namespace thodd::meta;

static_assert(is_array((int[]){}));
static_assert(!is_array(int{}));

struct base{};
struct derived : public base{};

static_assert(is_base_of(base{}, derived{}));
static_assert(!is_base_of(derived{}, base{}));

static_assert(is_class(base{}));
static_assert(!is_class(int{}));

struct not_empty
{
    int i;
};

static_assert(is_empty(base{}));
static_assert(!is_empty(not_empty{}));

enum class day
{
    MONDAY, 
    SUNDAY
};

static_assert(is_enum(day{}));
static_assert(!is_enum(base{}));

static_assert(is_floating_point(double{}));
static_assert(!is_floating_point(int{}));

static_assert(is_integral(int{}));
static_assert(!is_integral(double{}));

extern constexpr int toto{0};

static_assert(is_lvalue_reference(toto));
static_assert(!is_lvalue_reference(double{}));

static_assert(!is_rvalue_reference(toto));
static_assert(is_rvalue_reference(double{}));

static_assert(is_nullptr(std::nullptr_t{}));
static_assert(!is_nullptr(int{}));

static_assert(is_pointer((int*) nullptr));
static_assert(!is_pointer(int{}));


