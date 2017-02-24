#ifndef __THODD_LANG_REGEX_HPP__
#  define __THODD_LANG_REGEX_HPP__

#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>
#  include <thodd/containers.hpp>

namespace thodd::lang
{
    template<
        typename algo_t>
    struct regex
    {
        algo_t algo;

        constexpr auto
        operator() (
            auto&&... __params) const 
        -> decltype(auto)
        {
            return regex{algo(perfect<decltype(__params)>(__params)...)};
        }
    };


    constexpr auto 
    make_regex(
        auto&& __algo)
    {
        return 
        regex<meta::decay<decltype(__algo)>>
        {perfect<decltype(__algo)>(__algo)};
    }


    template<  
        typename algo_t>
    inline auto 
    matches(
        regex<algo_t> const& __regex, 
        auto& __cursor, 
        auto const& __end)
    {
        auto __res = false;
        
        if(__cursor != __end)
            __res = __regex.algo(__cursor, __end);

        return __res;
    }
    
}

#endif