#ifndef __THODD_META_TRAITS_ADD_RVALUE_REFERENCE_HPP__
#  define __THODD_META_TRAITS_ADD_RVALUE_REFERENCE_HPP__

#  include <thodd/meta/type.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr type_<type_t &&>
    add_rvalue_reference(
        type_<type_t> const&)
    {
        return {};
    }


    template<
        typename type_t>
    using add_rvalue_reference_t = 
        __type<decltype(
            add_rvalue_reference(type_<type_t>{}))>;
}

#endif