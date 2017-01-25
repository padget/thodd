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
            matcher<alternative<lcases_t...>> const& __lalter,
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
            matcher<alternative<lcases_t...>> const& __lalter,
            matcher<alternative<rcases_t...>> const& __ralter)
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
            typename ... lalgos_t, 
            typename ralgo_t>
        constexpr auto
        operator | (
            matcher<follow<lalgos_t...>> const& __lalter,
            matcher<ralgo_t> const& __rmatcher)
        {
            return 
            make_matcher(
                make_follow(
                    __lalter.algo.algos 
                  + __rmatcher));
        }


        template<
            typename ... lalgos_t, 
            typename ... ralgos_t>
        constexpr auto
        operator | (
            matcher<follow<lalgos_t...>> const& __lalter,
            matcher<follow<ralgos_t...>> const& __ralter)
        {
            return 
            make_matcher(
                make_follow(
                    __lalter.algo.algos 
                  + __ralter.algo.algos));
        }
    }
}

#endif // !__THODD_LANG2_HPP__