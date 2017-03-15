#ifndef __THODD_META_TRAITS_IS_FLOATING_POINT_HPP__
#  define __THODD_META_TRAITS_IS_FLOATING_POINT_HPP__

#  include <thodd/meta/traits/is_same.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_floating_point(
       type_<type_t> const& __ltype) 
    {
       return
       is_same(type_<type_t>{}, type_<float>{})
       || is_same(type_<type_t>{}, type_<double>{})
       || is_same(type_<type_t>{}, type_<long double>{});
    }

    template<
        typename type_t>
    using is_floating_point_t = __type<decltype(is_floating_point(type_<type_t>{}))>;
}

#endif