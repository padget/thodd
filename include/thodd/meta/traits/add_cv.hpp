#ifndef __THODD_META_TRAITS_ADD_CV_HPP__
#  define __THODD_META_TRAITS_ADD_CV_HPP__

#  include <thodd/meta/type.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr type_<type_t const volatile>
    add_const(
        type_<type_t> const&)
    {
        return {};
    }
}

#endif