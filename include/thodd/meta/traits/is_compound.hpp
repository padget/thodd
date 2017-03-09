#ifndef __THODD_META_TRAITS_IS_COMPOUND_HPP__
#  define __THODD_META_TRAITS_IS_COMPOUND_HPP__

#  include <thodd/meta/traits/is_fundamental.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto 
    is_compound(
        type_<type_t> const&)
    {
        return 
        ! is_fundamental(
            type_<type_t>{});
    }
}

#endif