#ifndef __THODD_LANG_REGEX_OR_HPP__
#  define __THODD_LANG_REGEX_OR_HPP__

#  include <thodd/tuple/tuple.hpp>

namespace 
thodd::lang::regex
{
    template<
        typename ... choices_t>
    struct or_ 
    {
        tuple<choices_t...> choices ;
    } ;


    template<
        typename lalgo_t, 
        typename ralgo_t>
    constexpr or_<
                regex<lalgo_t>, 
                regex<ralgo_t>>
    operator | (
        regex<lalgo_t> const& __lregex, 
        regex<lalgo_t> const& __rregex)
    {
        return
        { make_tuple(__lregex, __rregex) } ;
    }


    template<
        typename ... algos_t, 
        typename ralgo_t>
    constexpr or_<
                regex<algos_t>..., 
                regex<ralgo_t>>
    operator | (
        or_<regex<algos_t>...> const& __or,
        regex<ralgo_t> const& __regex)
    {
        return 
        { __or.choices + make_tuple(__regex) } ;
    }
}

#endif