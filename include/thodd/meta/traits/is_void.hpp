#ifndef __THODD_META_TRAITS_IS_VOID_HPP_
#  define __THODD_META_TRAITS_IS_VOID_HPP_

#  include <thodd/meta/traits/is_same.hpp>

namespace 
thodd::meta
{
    constexpr auto
    is_void(
       auto const& __ltype) 
    {
       return is_same(__ltype, void{});
    }
}

#endif