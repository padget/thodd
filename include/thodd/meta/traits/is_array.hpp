#ifndef __THODD_META_TRAITS_IS_ARRAY_HPP_
#  define __THODD_META_TRAITS_IS_ARRAY_HPP_

#  include <thodd/meta/traits/is_same.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_array(
       type_<type_t> const&) 
    {
       return false;
    }

    template<
        typename type_t>
    constexpr auto 
    is_array(
        type_<type_t[]> const&)
    {
        return true;
    }
}

#endif