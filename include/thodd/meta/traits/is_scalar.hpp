#ifndef __THODD_META_TRAITS_IS_OBJECT_HPP_
#  define __THODD_META_TRAITS_IS_OBJECT_HPP_

#  include <thodd/meta/traits/is_arithmetic.hpp>
#  include <thodd/meta/traits/is_enum.hpp>
#  include <thodd/meta/traits/is_pointer.hpp>
#  include <thodd/meta/traits/is_member_pointer.hpp>
#  include <thodd/meta/traits/is_nullptr.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_nullptr(
       type_<type_t> const&) 
    {
       return
       is_arithmetic(type_<type_t>{})
       || is_enum(type_<type_t>{})
       || is_pointer(type_<type_t>{})
       || is_member_pointer(type_<type_t>{})
       || is_nullptr(type_<type_t>{});
    }

    template<
        typename type_t>
    using is_scalar_t = __type<decltype(is_scalar(type_<type_t>{}))>;
}

#endif