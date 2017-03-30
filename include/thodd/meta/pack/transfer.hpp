#ifndef __THODD_META_PACK_TRANSFER_HPP__
#  define __THODD_META_PACK_TRANSFER_HPP__

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        template<
            typename ...>
        typename to_t,
        template<
            typename ...>
        typename from_t,
        typename ... types_t>
    constexpr to_t<types_t...>
    transfer(
        from_t<types_t...> const&)
    {
        return {};
    }


    template<
        template<
            typename ...>
        typename to_t,
        template<
            typename ...>
        typename from_t,
        typename ... types_t>
    using transfer_t = 
        decltype(transfer<to_t>(from_t<types_t...>{}));
}

#endif