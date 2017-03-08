#ifndef __THODD_META_TRAITS_IS_NULLPTR_HPP_
#  define __THODD_META_TRAITS_IS_NULLPTR_HPP_

#  include <thodd/meta/traits/is_same.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_nullptr(
       type_<type_t> const&) 
    {
       return
       is_same(
           type_<type_t>{}, 
           type_<std::nullptr_t>{});
    }
}

#endif