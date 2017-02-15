#ifndef __THODD_LANG_RULE_HPP__
#  define __THODD_LANG_RULE_HPP__

namespace thodd
{
    namespace lang
    {
        template<
            typename algo_t,
            typename reactor_t>
        struct rule
        {
            algo_t algo;
            reactor_t reactor;

            constexpr auto
            operator() (
                auto&&... __params) const 
            -> decltype(auto)
            {
                return rule{algo(perfect<decltype(__params)>(__params)...)};
            }
        };

        constexpr auto
        make_rule(
            auto&& __algo,
            auto&& __reactor)
        -> decltype(auto)
        {
            using algo_t = decltype(__algo);
            using reactor_t = decltype(__reactor);
            
            return 
            rule<
                meta::decay<algo_t>,
                meta::decay<reactor_t>>
            {perfect<algo_t>(__algo),
             perfect<reactor_t>(__reactor)};
        }

        template<
            typename algo_t,
            typename reactor_t>
        inline auto
        matches(
            rule<word<algo_t>, reactor_t> const& __rule,
            auto& __cursor,
            auto const& __end, 
            auto& __target)
        {
            auto __tokens = matches(__rule.algo, __cursor, __end);

            if((bool) __tokens)
                __rule.reactor(__tokens, __target);
        }


        template<
            typename algo_t, 
            typename reactor_t>
        inline auto 
        matches(
            rule<algo_t, reactor_t> const& __rule
            auto& __cursor, 
            auto const& __end, 
            auto& __target)
        {
            matches()
        }
    }
}

#endif