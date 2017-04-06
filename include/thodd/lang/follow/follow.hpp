#ifndef __THODD_LANG_FOLLOW_HPP__
#  define __THODD_LANG_FOLLOW_HPP__

#  include <thodd/tuple/tuple.hpp>
#  include <thodd/tuple/dynamic_tuple.hpp>

#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/meta/traits/remove_pointer.hpp>
#  include <thodd/core/declval.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/sequence.hpp>
#  include <thodd/core/infinity.hpp>

#  include <thodd/lang/core/core.hpp>
#  include <thodd/lang/core/regex.hpp>
#  include <thodd/lang/core/word.hpp> 

namespace thodd::lang
{
    template<
        typename ... algos_t>
    struct follow
    {
        tuple<algos_t...> algos;
    };

    template<
        typename ... algos_t>
    constexpr auto 
    make_follow(
        tuple<algos_t...> const& __algos)
    {
        return 
        follow<meta::decay_t<algos_t>...>
        {__algos};
    }


    template<
        typename lalgo_t, 
        typename ralgo_t>
    constexpr auto
    operator >> (
        regex<lalgo_t> const& __lregex,
        regex<ralgo_t> const& __rregex )
    {
        return 
        make_regex(
            make_follow(
                make_tuple(
                    __lregex, 
                    __rregex)));   
    }

        template<
        typename ... lcases_t, 
        typename rcase_t>
    constexpr auto
    operator >> (
        regex<follow<regex<lcases_t>...>> const& __lfollow,
        regex<rcase_t> const& __rregex)
    {
        return 
        make_regex(
            make_follow(
                __lfollow.algo.algos 
                + make_tuple(__rregex)));
    }


    template<
        typename ... lcases_t, 
        typename ... rcases_t>
    constexpr auto
    operator >> (
        regex<follow<regex<lcases_t>...>> const& __lfollow,
        regex<follow<regex<rcases_t>...>> const& __rfollow)
    {
        return 
        make_regex(
            make_follow(
                __lfollow.algo.algos 
                + __rfollow.algo.algos));
    }




    template<
        typename lalgo_t,
        typename lcaster_t, 
        typename ralgo_t,
        typename rcaster_t>
    constexpr auto
    operator >> (
        word<lalgo_t, lcaster_t> const& __lword,
        word<ralgo_t, rcaster_t> const& __rword )
    {
        return 
        make_word(
            make_follow(
                make_tuple(
                    __lword, 
                    __rword)));   
    }

    
    template<
        typename ... lcases_t, 
        typename ... lcasters_t,
        typename lcaster_t,
        typename rcase_t, 
        typename rcaster_t>
    constexpr auto
    operator >> (
        word<follow<word<lcases_t, lcasters_t>...>, lcaster_t> const& __lfollow,
        word<rcase_t, rcaster_t> const& __rword)
    {
        return 
        make_word(
            make_follow(
                __lfollow.algo.algos 
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
    operator >> (
        word<follow<word<lcases_t, lcasters_t>...>, lcaster_t> const& __lfollow,
        word<follow<word<rcases_t, rcasters_t>...>, rcaster_t> const& __rfollow)
    {
        return 
        make_word(
            make_follow(
                __lfollow.algo.algos 
                + __rfollow.algo.algos));
    }
}

#endif