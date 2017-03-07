#ifndef __THODD_META_TRAITS_IS_FLOATING_POINT_HPP__
#  define __THODD_META_TRAITS_IS_FLOATING_POINT_HPP__

#  include <thodd/meta/traits/is_same.hpp>
#  include <thodd/core_or.hpp>

namespace 
thodd::meta
{
    constexpr auto
    is_integral(
       auto const& __ltype) 
    {
       return
       thodd::or_(
            is_same(__ltype, float{}),
            is_same(__ltype, double{}),
            is_same(__ltype, long double{}));
    }
}

#endif