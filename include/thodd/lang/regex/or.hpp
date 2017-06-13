#ifndef __THODD_LANG_REGEX_OR_HPP__
#  define __THODD_LANG_REGEX_OR_HPP__

#  include <thodd/tuple/tuple.hpp>
#  include <thodd/lang/regex/regex.hpp>
#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/core/perfect.hpp>

namespace 
thodd::lang::regex
{
    template<
        typename ... choices_t>
    struct or_ : regex
    {
        tuple<choices_t...> choices ;

        constexpr or_(
            auto&& __choices) :
            choices { perfect<decltype(__choices)>(__choices) } {}
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
            perfect<decltype(__rregex)>(__rregex)) } ;
    }


    template<
        typename ... lregexs_t>
    constexpr auto
    operator | (
        or_<lregexs_t...> const& __or,
        auto&& __rregex)
    {
        static_assert(is_regex_based(__rregex)) ;

        using namespace thodd::meta;

        return 
        or_<lregexs_t..., decay_t<decltype(__rregex)>>
        { __or.choices + make_tuple(perfect<decltype(__rregex)>(__rregex)) } ;
    }
}

#endif