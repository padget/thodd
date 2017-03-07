#ifndef __THODD_META_TRAITS_IS_LVALUE_REFERENCE_HPP__
#  define __THODD_META_TRAITS_IS_LVALUE_REFERENCE_HPP__

namespace 
thodd::meta
{
    constexpr auto 
    is_lvalue_reference(
        auto&&)
    {
        return false;
    }

    template<
        typename type_t>
    constexpr auto 
    is_lvalue_reference(
        type_t&) 
    {
        return true;
    }
}

#endif