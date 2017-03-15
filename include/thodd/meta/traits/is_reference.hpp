#ifndef __THODD_META_TRAITS_IS_REFERENCE_HPP__
#  define __THODD_META_TRAITS_IS_REFERENCE_HPP__

#  include <thodd/meta/traits/is_lvalue_reference.hpp>
#  include <thodd/meta/traits/is_rvalue_reference.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto 
    is_reference(
        type_<type_t> const&)
    {
        return 
        is_lvalue_reference(type_<type_t>{})
        || is_rvalue_reference(type_<type_t>{});
    }

    template<
        typename type_t>
    using is_reference_t = __type<decltype(is_reference(type_<type_t>{}))>;
}

#endif