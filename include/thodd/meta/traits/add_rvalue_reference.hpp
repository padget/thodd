#ifndef __THODD_META_TRAITS_ADD_RVALUE_REFERENCE_HPP__
#  define __THODD_META_TRAITS_ADD_RVALUE_REFERENCE_HPP__

namespace
thodd::meta
{
    constexpr auto&&
    add_rvalue_reference(
        auto __t)
    {
        return __t;
    }
}

#endif