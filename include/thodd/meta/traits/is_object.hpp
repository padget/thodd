#ifndef __THODD_META_TRAITS_IS_OBJECT_HPP_
#  define __THODD_META_TRAITS_IS_OBJECT_HPP_

#  include <thodd/meta/traits/is_scalar.hpp>
#  include <thodd/meta/traits/is_array.hpp>
#  include <thodd/meta/traits/is_union.hpp>
#  include <thodd/meta/traits/is_class.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_object(
       type_<type_t> const&) 
    {
       return
       is_scalar(type_<type_t>{})
       || is_array(type_<type_t>{})
       || is_union(type_<type_t>{})
       || is_class(type_<type_t>{});
    }

    template<
        typename type_t>
    using is_object_t = __type<decltype(is_object(type_<type_t>{}))>;
}

#endif