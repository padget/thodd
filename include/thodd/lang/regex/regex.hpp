#ifndef __THODD_LANG_REGEX_REGEX_HPP__
#  define __THODD_LANG_REGEX_REGEX_HPP__

#  include <thodd/core/perfect.hpp>
#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::lang::regex
{
    template< 
        typename algo_t>
    struct regex
    {
        algo_t algo ;
    } ;

    constexpr auto
    make_regex(
        auto&& __algo)
    {
        using algo_t  = decltype(__algo) ;
        using algod_t = meta::decay_t<algo_t> ;

        return
        regex<algod_t>
        { perfect<algo_t>(__algo) } ;
    }
}

#endif