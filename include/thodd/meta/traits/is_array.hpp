#ifndef __THODD_META_TRAITS_ARRAY_HPP_
#  define __THODD_META_TRAITS_ARRAY_HPP_

#  include <thodd/meta/traits/is_same.hpp>

namespace 
thodd::meta
{
    constexpr auto
    is_void(
       auto const& __ltype) 
    {
       return false;
    }

    template<
        typename type_t>
    constexpr auto 
    is_array(type_t[])
    {
        return true;
    }
}

#endif