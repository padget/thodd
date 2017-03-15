#ifndef __THODD_META_TRAITS_IS_UNION_HPP__
#  define __THODD_META_TRAITS_IS_UNION_HPP__

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_union(
       type_<type_t> const&) 
    {
        return
        __is_union(type_t);
    }

    template<
        typename type_t>
    using is_union_t = __type<decltype(is_union(type_<type_t>{}))>;
}

#endif