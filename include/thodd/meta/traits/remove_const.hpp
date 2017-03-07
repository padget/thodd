#ifndef __THODD_META_TRAITS_REMOVE_CONST_HPP__
#  define __THODD_META_TRAITS_ADD_REMOVE_CONST_HPP__

namespace
thodd::meta
{
    constexpr auto&
    add_volatile(
        auto __t)
    {
        return __t;
    }
}

#endif