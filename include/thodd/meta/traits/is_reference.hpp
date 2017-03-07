#ifndef __THODD_META_TRAITS_IS_REFERENCE_HPP__
#  define __THODD_META_TRAITS_IS_REFERENCE_HPP__

#  include <thodd/meta/traits/is_lvalue_reference.hpp>
#  include <thodd/meta/traits/is_rvalue_reference.hpp>

namespace 
thodd::meta
{
    constexpr auto 
    is_reference(
        auto&& __t)
    {
        return 
        is_lvalue_reference(__t);
        || is_rvalue_reference(__t);
    }
}

#endif