#ifndef __THODD_LANG_REGEX_AND_HPP__
#  define __THODD_LANG_REGEX_AND_HPP__

#  include <thodd/tuple/tuple.hpp>

namespace 
thodd::lang::regex
{
    template<
        typename ... regexs_t>
    struct and_ 
    {
        tuple<regexs_t...> regexs ;
    } ;


    template<
        typename lalgo_t, 
        typename ralgo_t>
    constexpr and_<
                regex<lalgo_t>, 
                regex<ralgo_t>>
    operator > (
        regex<lalgo_t> const& __lregex, 
        regex<lalgo_t> const& __rregex)
    {
        return
        { make_tuple(__lregex, __rregex) } ;
    }


    template<
        typename ... algos_t, 
        typename ralgo_t>
    constexpr and_<
                regex<algos_t>..., 
                regex<ralgo_t>>
    operator | (
        and_<regex<algos_t>...> const& __or,
        regex<ralgo_t> const& __regex)
    {
        return 
        { __or.choices + make_tuple(__regex) } ;
    }
}
