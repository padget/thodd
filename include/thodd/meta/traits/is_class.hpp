#ifndef __THODD_META_TRAITS_IS_CLASS_HPP__
#  define __THODD_META_TRAITS_IS_CLASS_HPP__

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_class(
       type_<type_t> const&) 
    {
        return
        __is_class(type_t);
    }


    template<
        typename type_t>
    using is_class_t = __type<decltype(is_class(type_<type_t>{}))>;
}

#endif