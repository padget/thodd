#ifndef __THODD_META_TRAITS_IS_ENUM_HPP__
#  define __THODD_META_TRAITS_IS_ENUM_HPP__

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_enum(
       type_<type_t> const&) 
    {
        return
        __is_enum(type_t);
    }
}

#endif