#ifndef __THODD_META_TRAITS_IS_BASE_OF_HPP_
#  define __THODD_META_TRAITS_IS_BASE_OF_HPP_

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename base_t, 
        typename derived_t>
    constexpr auto
    is_base_of(
        type_<base_t> const&,
        type_<derived_t> const&) 
    {
       return 
       __is_base_of(
           base_t, 
           derived_t);
    }
}

#endif