#ifndef __THODD_META_PACK_CONCAT_HPP__
#  define __THODD_META_PACK_CONCAT_HPP__

namespace 
thodd::meta
{
    template<
        template<
            typename ...>
        typename left_t, 
        typename ... lefts_t>
    constexpr left_t<lefts_t...> 
    concat(
        left_t<lefts_t...> const&)
    {
        return {};
    }


    template<
        template<
            typename ...>
        typename left_t, 
        typename ... lefts_t, 
        template<
            typename ...>
        typename right_t, 
        typename ... rights_t, 
        typename ... nexts_t>
    constexpr auto
    concat(
        left_t<lefts_t...> const&,
        right_t<rights_t...> const&,
        nexts_t const&...)
    {
        return 
        concat(
            left_t<lefts_t..., rights_t...>{}, 
            nexts_t{}...);
    }   
}

#endif