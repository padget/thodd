#ifndef __THODD_META_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP__
#  define __THODD_META_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP__

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto 
    is_member_function_pointer(
        type_<type_t> const&)
    {
        return false;
    }

    template<
        typename type_t, 
        typename class_t>
    constexpr auto 
    is_member_function_pointer(
        type_<type_t class_t::*> const&) 
    {
        return 
        is_function(
            type_<type_t class_t::*>{});
    }

    template<
        typename type_t>
    using is_member_function_pointer_t = __type<decltype(is_member_function_pointer(type_<type_t>{}))>;
}

#endif