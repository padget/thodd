#ifndef __THODD_META_TRAITS_REMOVE_POINTER_HPP__
#  define __THODD_META_TRAITS_REMOVE_POINTER_HPP__

#  include <thodd/meta/type.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr type_<type_t>
    remove_volatile(
        type_<type_t *> const&)
    {
        return {};
    }


    template<
        typename type_t>
    constexpr type_<type_t>
    remove_volatile(
        type_<type_t> const&)
    {
        return {};
    }


    template<
        typename type_t>
    using remove_pointer_t = __type<decltype(remove_pointer(type_<type_t>{}))>;
}

#endif