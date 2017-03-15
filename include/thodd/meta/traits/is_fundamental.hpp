#ifndef __THODD_META_TRAITS_IS_FUNDAMENTAL_HPP_
#  define __THODD_META_TRAITS_IS_FUNDAMENTAL_HPP_

#  include <thodd/meta/traits/is_arithmetic.hpp>
#  include <thodd/meta/traits/is_void.hpp>
#  include <thodd/meta/traits/is_nullptr.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto 
    is_fundamental(
        type_<type_t> const&)
    {
        return
        is_arithmetic(type_<type_t>{})
        || is_nullptr(type_<type_t>{})
        || is_void(type_<type_t>{});
    }

    template<
        typename type_t>
    using is_fundamental_t = __type<decltype(is_fundamental(type_<type_t>{}))>;
}

#endif