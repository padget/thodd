#ifndef __THODD_META_TRAITS_IS_INTEGRAL_HPP__
#  define __THODD_META_TRAITS_IS_INTEGRAL_HPP__

#  include <thodd/meta/traits/is_same.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_integral(
       type_<type_t> const&) 
    {
       return
        is_same(type_<type_t>{}, type_<bool>{}) 
        || is_same(type_<type_t>{}, type_<unsigned char>{}) 
        || is_same(type_<type_t>{}, type_<signed char>{})
        || is_same(type_<type_t>{}, type_<char16_t>{})
        || is_same(type_<type_t>{}, type_<char32_t>{})
        || is_same(type_<type_t>{}, type_<wchar_t>{})
        || is_same(type_<type_t>{}, type_<unsigned short>{})
        || is_same(type_<type_t>{}, type_<unsigned int>{})
        || is_same(type_<type_t>{}, type_<unsigned long>{})
        || is_same(type_<type_t>{}, type_<unsigned long long>{})
        || is_same(type_<type_t>{}, type_<short>{})
        || is_same(type_<type_t>{}, type_<int>{})
        || is_same(type_<type_t>{}, type_<long>{})
        || is_same(type_<type_t>{}, type_<long long>{})
        || is_same(type_<type_t>{}, type_<signed short>{})
        || is_same(type_<type_t>{}, type_<signed int>{})
        || is_same(type_<type_t>{}, type_<signed long>{})
        || is_same(type_<type_t>{}, type_<signed long long>{});
    }


    template<
        typename type_t>
    using is_integralc_t = __type<decltype(is_integral(type_<type_t>{}))>;
}

#endif