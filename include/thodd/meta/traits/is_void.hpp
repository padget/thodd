#ifndef __THODD_META_TRAITS_IS_VOID_HPP_
#  define __THODD_META_TRAITS_IS_VOID_HPP_

#  include <thodd/meta/traits/is_same.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_void(
       type_<type_t> const&) 
    {
        return 
        is_same(
            type_<type_t>{}, 
            type_<void>{});
    }

    template<
        typename type_t>
    using is_void_t = __type<decltype(is_void(type_<type_t>{}))>;
}

#endif