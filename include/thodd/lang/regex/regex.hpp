#ifndef __THODD_LANG_REGEX_REGEX_HPP__
#  define __THODD_LANG_REGEX_REGEX_HPP__

#  include <thodd/core/perfect.hpp>

namespace 
thodd::lang::regex
{
    template< 
        typename algo_t>
    struct regex
    {
        algo_t algo;

        constexpr auto
        operator () (
            auto&&... __params) const 
        -> decltype(auto)
        {
            return 
            regex
            { algo(perfect<decltype(__params)>(__params)...) };
        }
    };
}

#endif