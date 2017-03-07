#ifndef __THODD_META_TRAITS_ADD_POINTER_HPP__
#  define __THODD_META_TRAITS_ADD_POINTER_HPP__

namespace
thodd::meta
{
    constexpr auto*
    add_pointer(
        auto __t)
    {
        return &__t;
    }
}

#endif