#ifndef __THODD_LANG_RULE_HPP__
#  define __THODD_LANG_RULE_HPP__

namespace thodd
{
    namespace lang
    {
        template<
            typename algo_t,
            typename caster_t>
        struct rule
        {
            algo_t algo;
            caster_t caster;

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
            auto&& __caster)
        -> decltype(auto)
        {
            using algo_t = decltype(__algo);
            using caster_t = decltype(__caster);
            
            return 
            rule<
                meta::decay<algo_t>,
                meta::decay<caster_t>>
            {perfect<algo_t>(__algo),
             perfect<caster_t>(__caster)};
        }

        template<
            typename algo_t,
            typename caster_t>
        inline auto
        matches(
            rule<word<algo_t>, caster_t> const& __rule,
            auto& __cursor,
            auto const& __end, 
            auto& __target)
        {
            auto __tokens = matches(__rule.algo, __cursor, __end);

            if((bool) __tokens)
                __rule.caster(__tokens, __target);
        }


        template<
            typename algo_t, 
            typename caster_t>
        inline auto 
        matches(
            rule<algo_t, caster_t> const& __rule
            auto& __cursor, 
            auto const& __end, 
            auto& __target)
        {
            matches()
        }
    }
}

#endif