#ifndef __THODD_META_TRAITS_IS_RVALUE_REFERENCE_HPP__
#  define __THODD_META_TRAITS_IS_RVALUE_REFERENCE_HPP__

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto 
    is_rvalue_reference(
        type_<type_t> const&)
    {
        return false;
    }

    template<
        typename type_t>
    constexpr auto 
    is_rvalue_reference(
        type_<type_t&&> const&) 
    {
        return true;
    }

    template<
        typename type_t>
    using is_rvalue_reference_t = __type<decltype(is_rvalue_reference(type_<type_t>{}))>;
}

#endif