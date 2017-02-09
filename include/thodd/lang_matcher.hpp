#ifndef __THODD_LANG_MATCHER_HPP__
#  define __THODD_LANG_MATCHER_HPP__

#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>
#  include <thodd/containers.hpp>

namespace thodd
{
    namespace lang
    {
        template<
            typename algo_t>
        struct matcher
        {
            algo_t algo;

            constexpr auto
            operator() (
                auto&&... __params) const 
            -> decltype(auto)
            {
                return matcher{algo(perfect<decltype(__params)>(__params)...)};
            }
        };


        constexpr auto 
        make_matcher(
            auto&& __algo)
        {
            return 
            matcher<meta::decay<decltype(__algo)>>
            {perfect<decltype(__algo)>(__algo)};
        }


        template<  
            typename algo_t>
        inline auto 
        matches(
            matcher<algo_t> const& __matcher, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __res = false;
            
            if(__cursor != __end)
                __res = __matcher.algo(__cursor, __end);

            return __res;
        }
    }
}

#endif