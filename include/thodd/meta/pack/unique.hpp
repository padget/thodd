#ifndef __THODD_META_PACK_UNIQUE_HPP__
#  define __THODD_META_PACK_UNIQUE_HPP__

#  include <thodd/meta/pack/concat.hpp>
#  include <thodd/meta/utils/if.hpp>
#  include <thodd/meta/pack/contains.hpp>

namespace 
thodd::meta
{
    template<
        template<
            typename ...> 
        typename pack_t>
    constexpr pack_t<> 
    unique(
        pack_t<> const&)
    {
        return {};
    }


    template<
        template<
            typename...>
        typename pack_t,
        typename type_t,
        typename ... types_t>
    constexpr auto
    unique(
        pack_t<type_t, types_t...> const)
    {
        return 
        concat(
            if_(
                contains(
                    pack_t<types_t...>{}, 
                    type_<type_t>{}),
                pack_t<>{}, 
                pack_t<type_t>{}), 
            unique(pack_t<types_t...>{}));
    }
}

#endif