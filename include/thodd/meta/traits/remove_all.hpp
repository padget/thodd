#ifndef __THODD_META_TRAITS_REMOVE_ALL_HPP__
#  define __THODD_META_TRAITS_REMOVE_ALL_HPP__

#  include <thodd/meta/type.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    remove_const(
        type_<type_t> const&)
    {
        return 
        remove_reference(
            remove_cv(
                remove_pointer(
                    type_<type_t>)));
    }
}

#endif