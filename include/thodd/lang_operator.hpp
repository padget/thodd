#ifndef __THODD_LANG_OPERATOR_HPP__
#  define __THODD_LANG_OPERATOR_HPP__

#  include<thodd/lang_matcher.hpp>
#  include<thodd/lang_alternative.hpp>

namespace thodd
{
    namespace lang
    {
        template<
            typename lcase_t, 
            typename rcase_t>
        constexpr auto
        operator | (
            matcher<lcase_t> const& __lmatcher,
            matcher<rcase_t> const& __rmatcher )
        {
            return 
            make_matcher(
                make_alternative(
                    __lmatcher, 
                    __rmatcher));   
        }


        template<
            typename ... lcases_t, 
            typename rcase_t>
        constexpr auto
        operator | (
            matcher<alternative<matcher<lcases_t>...>> const& __lalter,
            matcher<rcase_t> const& __rmatcher)
        {
            return 
            make_matcher(
                make_alternative(
                    __lalter.algo.cases 
                  + __rmatcher));
        }


        template<
            typename ... lcases_t, 
            typename ... rcases_t>
        constexpr auto
        operator | (
            matcher<alternative<matcher<lcases_t>...>> const& __lalter,
            matcher<alternative<matcher<rcases_t>...>> const& __ralter)
        {
            return 
            make_matcher(
                make_alternative(
                    __lalter.algo.cases 
                  + __ralter.algo.cases));
        }

        template<
            typename rcase_t>
        constexpr auto
        operator ~ (
            matcher<rcase_t> const& __rmatcher )
        {
            return 
            make_some( 
                __rmatcher);   
        }


        template<
            typename lalgo_t, 
            typename ralgo_t>
        constexpr auto
        operator >> (
            matcher<lalgo_t> const& __lmatcher,
            matcher<ralgo_t> const& __rmatcher )
        {
            return 
            make_matcher(
                make_follow(
                    __lmatcher, 
                    __rmatcher));   
        }

         template<
            typename ... lcases_t, 
            typename rcase_t>
        constexpr auto
        operator >> (
            matcher<follow<matcher<lcases_t>...>> const& __lalter,
            matcher<rcase_t> const& __rmatcher)
        {
            return 
            make_matcher(
                make_follow(
                    __lalter.algo.algos 
                  + __rmatcher));
        }


        template<
            typename ... lcases_t, 
            typename ... rcases_t>
        constexpr auto
        operator >> (
            matcher<follow<matcher<lcases_t>...>> const& __lalter,
            matcher<follow<matcher<rcases_t>...>> const& __ralter)
        {
            return 
            make_matcher(
                make_follow(
                    __lalter.algo.algos 
                  + __ralter.algo.algos));
        }

        


        template<
            typename lcase_t, 
            typename rcase_t>
        constexpr auto
        operator | (
            rule<lcase_t> const& __lrule,
            rule<rcase_t> const& __rrule)
        {
            return 
            make_rule(
                make_alternative(
                    __lrule, 
                    __rrule));   
        }


        template<
            typename ... lalgos_t, 
            typename ralgo_t>
        constexpr auto
        operator | (
            rule<alternative<rule<lalgos_t>...>> const& __lalter,
            rule<ralgo_t> const& __rrule)
        {
            return 
            make_rule(
                make_alternative(
                    __lalter.algo.algos 
                  + __rrule));
        }

        template<
            typename ... lcases_t, 
            typename ... rcases_t>
        constexpr auto
        operator | (
            rule<alternative<rule<lcases_t>...>> const& __lalter,
            rule<alternative<rule<rcases_t>...>> const& __ralter)
        {
            return 
            make_rule(
                make_alternative(
                    __lalter.algo.cases 
                  + __ralter.algo.cases));
        }


        template<
            typename rcase_t>
        constexpr auto
        operator ~ (
            rule<rcase_t> const& __rrule)
        {
            return 
            make_some( 
                __rrule);   
        }



           template<
            typename lalgo_t, 
            typename ralgo_t>
        constexpr auto
        operator >> (
            rule<lalgo_t> const& __lrule,
            rule<ralgo_t> const& __rrule )
        {
            return 
            make_rule(
                make_follow(
                    __lrule, 
                    __rrule));   
        }

         template<
            typename ... lcases_t, 
            typename rcase_t>
        constexpr auto
        operator >> (
            rule<follow<rule<lcases_t>...>> const& __lalter,
            rule<rcase_t> const& __rrule)
        {
            return 
            make_rule(
                make_follow(
                    __lalter.algo.algos 
                  + __rrule));
        }


        template<
            typename ... lcases_t, 
            typename ... rcases_t>
        constexpr auto
        operator >> (
            rule<follow<rule<lcases_t>...>> const& __lalter,
            rule<follow<rule<rcases_t>...>> const& __ralter)
        {
            return 
            make_rule(
                make_follow(
                    __lalter.algo.algos 
                  + __ralter.algo.algos));
        }
    }
}

#endif // !__THODD_LANG2_HPP__