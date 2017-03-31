#ifndef __THODD_META_PACK_CONTAINS_HPP__
#  define __THODD_META_PACK_CONTAINS_HPP__

#  include <thodd/core/or.hpp>

#  include <thodd/meta/traits/is_same.hpp>
#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        template<
            typename ...>
        typename pack_t,
        typename ... types_t,
        typename type_t>
    constexpr auto 
    contains(
        pack_t<types_t...> const&, 
        type_<type_t> const&)
    {
        return 
        thodd::or_c(
            is_same(
                type_<types_t>{}, 
                type_<type_t>{})...);
    }
}

#endif