#ifndef __THODD_META_TRAITS_REMOVE_VOLATILE_HPP__
#  define __THODD_META_TRAITS_REMOVE_VOLATILE_HPP__

#  include <thodd/meta/type.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr type_<type_t>
    remove_volatile(
        type_<type_t volatile> const&)
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
    using remove_volatile_t = __type<decltype(remove_volatile(type_<type_t>{}))>;
}

#endif