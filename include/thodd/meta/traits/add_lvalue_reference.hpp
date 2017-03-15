#ifndef __THODD_META_TRAITS_ADD_LVALUE_REFERENCE_HPP__
#  define __THODD_META_TRAITS_ADD_LVALUE_REFERENCE_HPP__

#  include <thodd/meta/type.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr type_<type_t &>
    add_lvalue_reference(
        type_<type_t> const&)
    {
        return {};
    }


    template<
        typename type_t>
    using add_lvalue_reference_t = __type<decltype(add_lvalue_reference(type_<type_t>{}))>;
}

#endif