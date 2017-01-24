#ifndef __THODD_LANG_RULE_HPP__
#  define __THODD_LANG_RULE_HPP__

namespace thodd
{
    namespace lang
    {
        template<
            typename algo_t>
        struct rule
        {
            matcher<algo_t> match;
        };



        template<
            typename algo_t>
        constexpr auto 
        make_rule(
            matcher<algo_t> const& __matcher)
        {
            return rule<algo_t>{__matcher};
        }


        template<
            typename algo_t>
        inline auto 
        matches(
            rule<algo_t> const& __rule, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __save = __cursor;

            if(!matches(__rule.match , __cursor, __end))
                __cursor = __save;

            return token(__save, __cursor);
        }
    }
}

#endif