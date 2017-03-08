#ifndef __THODD_META_TRAITS_IS_POINTER_HPP__
#  define __THODD_META_TRAITS_IS_POINTER_HPP__

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto 
    is_pointer(
        type_<type_t> const&)
    {
        return false;
    }

    template<
        typename type_t>
    constexpr auto 
    is_pointer(
        type_<type_t*> const&) 
    {
        return true;
    }
}

#endif