#ifndef __THODD_LANG_ALTERNATIVE_ALTERNATIVE_HPP__
#  define __THODD_LANG_ALTERNATIVE_ALTERNATIVE_HPP__

#  include <thodd/tuple/tuple.hpp>
#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/core/perfect.hpp>

#  include <thodd/lang/core/regex.hpp>
#  include <thodd/lang/core/word.hpp>

namespace thodd::lang
{
    template<
        typename ... cases_t>
    struct alternative
    {
        tuple<cases_t...> cases;
    };
    
    
    template<
        typename ... cases_t>
    constexpr auto 
    make_alternative(
        tuple<cases_t...> const& __cases)
    {
        return 
        alternative<meta::decay_t<cases_t>...>
        { __cases };
    } 


    constexpr auto 
    make_alternative(
        auto&&... __cases)
    {
        return 
        alternative<meta::decay_t<decltype(__cases)>...>
        { make_tuple(perfect<decltype(__cases)>(__cases)...) };
    }


    template<
        typename lcase_t, 
        typename rcase_t>
    constexpr auto
    operator | (
        regex<lcase_t> const& __lregex,
        regex<rcase_t> const& __rregex )
    {
        return 
        make_regex(
            make_alternative(
                __lregex, 
                __rregex));   
    }


    template<
        typename ... lcases_t, 
        typename rcase_t>
    constexpr auto
    operator | (
        regex<alternative<regex<lcases_t>...>> const& __lalter,
        regex<rcase_t> const& __rregex)
    {
        return 
        make_regex(
            make_alternative(
                __lalter.algo.cases 
                + make_tuple(__rregex)));
    }


    template<
        typename ... lcases_t, 
        typename ... rcases_t>
    constexpr auto
    operator | (
        regex<alternative<regex<lcases_t>...>> const& __lalter,
        regex<alternative<regex<rcases_t>...>> const& __ralter)
    {
        return 
        make_regex(
            make_alternative(
                __lalter.algo.cases 
                + __ralter.algo.cases));
    }


    template<
        typename lcase_t, 
        typename lcaster_t,
        typename rcase_t, 
        typename rcaster_t>
    constexpr auto
    operator | (
        word<lcase_t, lcaster_t> const& __lword,
        word<rcase_t, rcaster_t> const& __rword)
    {
        return 
        make_word(
            make_alternative(
                __lword, 
                __rword));   
    }


    template<
        typename ... lalgos_t,
        typename ... lcasters_t,
        typename lcaster_t, 
        typename ralgo_t,
        typename rcaster_t>
    constexpr auto
    operator | (
        word<alternative<word<lalgos_t, lcasters_t>...>, lcaster_t> const& __lalter,
        word<ralgo_t, rcaster_t> const& __rword)
    {
        return 
        make_word(
            make_alternative(
                __lalter.algo.algos 
                + make_tuple(__rword)));
    }

    template<
        typename ... lcases_t,
        typename ... lcasters_t,
        typename lcaster_t, 
        typename ... rcases_t,
        typename ... rcasters_t, 
        typename rcaster_t>
    constexpr auto
    operator | (
        word<alternative<word<lcases_t, lcasters_t>...>, lcaster_t> const& __lalter,
        word<alternative<word<rcases_t, rcasters_t>...>, rcaster_t> const& __ralter)
    {
        return 
        make_word(
            make_alternative(
                __lalter.algo.cases 
                + __ralter.algo.cases));
    }
}

#endif