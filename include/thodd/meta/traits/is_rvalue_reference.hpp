#ifndef __THODD_META_TRAITS_IS_RVALUE_REFERENCE_HPP__
#  define __THODD_META_TRAITS_IS_RVALUE_REFERENCE_HPP__

namespace 
thodd::meta
{
    constexpr auto 
    is_rvalue_reference(
        auto&&)
    {
        return false;
    }

    template<
        typename type_t>
    constexpr auto 
    is_rvalue_reference(
        type_t&&) 
    {
        return true;
    }
}

#endif