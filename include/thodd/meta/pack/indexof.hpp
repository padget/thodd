#ifndef __THODD_META_PACK_INDEXOF_HPP__
#  define __THODD_META_PACK_INDEXOF_HPP__

#  include <thodd/meta/type.hpp>
#  include <thodd/meta/traits/is_same.hpp>

namespace 
thodd::meta
{
    template<
        template<
            typename ...>
        typename pack_t, 
        typename current_t>
    constexpr auto
    indexof(
        pack_t<> const&, 
        type_<current_t> const&)
    {
        return -1;
    }
    
    template<
        template<
            typename...>
        typename pack_t, 
        typename current_t,
        typename type_t, 
        typename ... types_t>
    constexpr auto
    indexof(
        pack_t<type_t, types_t...> const&,
        type_<current_t> const&)
    {
        auto __nindex = 
            indexof(
                pack_t<types_t...>{}, 
                type_<current_t>{});

        return 
        is_same(
            type_<type_t>{}, 
            type_<current_t>{}) ? 
        0 : (__nindex == -1 ? -1 : __nindex + 1);
    }
}

#endif