#ifndef __THODD_META_PACK_AT_HPP__
#  define __THODD_META_PACK_AT_HPP__

namespace 
thodd::meta 
{
    template<
        template<
            typename ... >
        typename pack_t, 
        typename type_t>
    constexpr type_<type_t>
    at(
        igral<size_t, 0> const&, 
        pack_t<type_t> const&)
    {
        return {};
    }


    template<
        size_t index_c, 
        template<
            typename ...>
        typename pack_t, 
        typename type_t,
        typename ... types_t>
    constexpr auto
    at( 
        igral<size_t, index_c> const&, 
        pack_t<type_t, types_t...> const&)
    {
        return 
        at(
            igral<size_t, index_c - 1>{},
            pack_t<types_t...>{});
    }
}

#endif