#ifndef __THODD_META_TRAITS_ADD_VOLATILE_HPP__
#  define __THODD_META_TRAITS_ADD_VOLATILE_HPP__

namespace
thodd::meta
{
    constexpr auto volatile
    add_volatile(
        auto __t)
    {
        return __t;
    }
}

#endif