#ifndef __THODD_META_TRAITS_IS_POINTER_HPP__
#  define __THODD_META_TRAITS_IS_POINTER_HPP__

namespace 
thodd::meta
{
    constexpr auto 
    is_pointer(
        auto&&)
    {
        return false;
    }

    template<
        typename type_t>
    constexpr auto 
    is_pointer(
        type_t*) 
    {
        return true;
    }
}

#endif