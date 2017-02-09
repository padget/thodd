#ifndef __THODD_LANG_RULE_HPP__
#  define __THODD_LANG_RULE_HPP__

#  include <thodd/lang_core.hpp>
#  include <thodd/lang_matcher.hpp>

namespace thodd
{
    namespace lang
    {
        template<
            typename algo_t>
        struct rule
        {
            algo_t algo;

            constexpr auto
            operator() (
                auto&&... __params) const 
            -> decltype(auto)
            {
                return rule{algo(perfect<decltype(__params)>(__params)...)};
            }
        };


        template<
            typename algo_t>
        constexpr auto 
        make_rule(
            algo_t&& __algo)
        {
            return rule<meta::decay<algo_t>>{perfect<algo_t>(__algo)};
        }


        template<
            typename algo_t>
        inline auto 
        matches(
            rule<matcher<algo_t>> const& __rule, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __save = __cursor;

            if(!matches(__rule.algo , __cursor, __end))
                __cursor = __save;

            return token(__save, __cursor);
        }


        template<
            typename algo_t>
        inline auto 
        matches(
            rule<algo_t> const& __rule, 
            auto& __cursor, 
            auto const& __end)
        {
            return matches(__rule.algo, __cursor, __end);
        }
    }
}

#endif