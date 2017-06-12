#ifndef __THODD_LANG_REGEX_OR_HPP__
#  define __THODD_LANG_REGEX_OR_HPP__

#  include <thodd/tuple/tuple.hpp>
#  include <thodd/lang/regex/regex.hpp>
#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::lang::regex
{
    template<
        typename ... choices_t>
    struct or_ : regex
    {
        tuple<choices_t...> choices ;
    } ;


    constexpr auto
    operator | (
        auto&& __lregex, 
        auto&& __rregex)
    {
        static_assert(is_regex_based(__lregex)) ;
        static_assert(is_regex_based(__rregex)) ;

        using namespace thodd::meta;

        return
        or_<
            decay_t<decltype(__lregex)>, 
            decay_t<decltype(__rregex)>>
        { make_tuple(
            perfect<decltype(__lregex)>(__lregex), 
            prefect<decltype(__rregex)>(__rregex)) } ;
    }


    template<
        typename ... choices_t>
    constexpr auto
    operator | (
        or_<lregexs_t...> const& __or,
        rregex_t&& __rregex)
    {
        static_assert(is_regex_based(__rregex)) ;

        using namespace thodd::meta;

        return 
        or_<choices_t..., decay_t<decltype(__rregex)>>
        { __or.choices + make_tuple(perfect<decltype(__rregex)>(__rregex)) } ;
    }
}

#endif