#ifndef __THODD_META_TRAITS_IS_ARITHMETIC_HPP__
#  define __THODD_META_TRAITS_IS_ARITHMETIC_HPP__

#  include <thodd/meta/traits/is_floating_point.hpp>
#  include <thodd/meta/traits/is_integral.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto 
    is_arithmetic(
        type_<type_t> const&)
    {
        return 
        is_floating_point(type_<type_t>{})
        || is_integral(type_<type_t>{});
    }

    template<
        typename type_t>
    using is_arithmetic_t = __type<decltype(is_arithmetic(type_<type_t>{}))>;
}

#endif 