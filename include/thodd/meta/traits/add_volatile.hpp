#ifndef __THODD_META_TRAITS_ADD_VOLATILE_HPP__
#  define __THODD_META_TRAITS_ADD_VOLATILE_HPP__

#  include <thodd/meta/type.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr type_<type_t volatile>
    add_volatile(
        type_<type_t> const&)
    {
        return {};
    }
}

#endif