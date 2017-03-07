#ifndef __THODD_META_TRAITS_IS_INTEGRAL_HPP__
#  define __THODD_META_TRAITS_IS_INTEGRAL_HPP__

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
            is_same(__ltype, bool{}),
            is_same(__ltype, unsigned char{}),
            is_same(__ltype, signed char{}),
            is_same(__ltype, char16_t{}),
            is_same(__ltype, char32_t{}),
            is_same(__ltype, wchar_t{}),
            is_same(__ltype, unsigned short{}),
            is_same(__ltype, unsigned int{}),
            is_same(__ltype, unsigned long{}),
            is_same(__ltype, unsigned long long{}),
            is_same(__ltype, short{}),
            is_same(__ltype, int{}),
            is_same(__ltype, long{}),
            is_same(__ltype, long long{}),
            is_same(__ltype, signed short{}),
            is_same(__ltype, signed int{}),
            is_same(__ltype, signed long{}),
            is_same(__ltype, signed long long{}));
    }
}

#endif