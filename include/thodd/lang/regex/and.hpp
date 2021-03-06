#ifndef __THODD_LANG_REGEX_AND_HPP__
#  define __THODD_LANG_REGEX_AND_HPP__

#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/tuple/tuple.hpp>

#  include <thodd/lang/regex/regex.hpp>

namespace 
thodd::lang::regex
{
    template<
        typename ... regexs_t>
    struct and_ : regex
    {
        tuple<regexs_t...> regexs ;

        constexpr and_(
            decltype(regexs) && __regexs):
            regexs { perfect<decltype(__regexs)>(__regexs) } {}

        constexpr and_(
            decltype(regexs) const & __regexs) :
            regexs { rvalue(__regexs) } {}

        constexpr and_(and_ const&) = default ;
        constexpr and_(and_&&) = default ;
        constexpr and_& operator = (and_ const &) = default ;
        constexpr and_& operator = (and_ &&) = default ;
    } ;

    constexpr auto
    operator > (
        auto&& __lregex, 
        auto&& __rregex)
    {
        static_assert(is_regex_based(__lregex)) ;
        static_assert(is_regex_based(__rregex)) ;

        using namespace thodd::meta ;

        return
        and_<
            decay_t<decltype(__lregex)>, 
            decay_t<decltype(__rregex)>>
        { make_tuple(
            perfect<decltype(__lregex)>(__lregex), 
            perfect<decltype(__rregex)>(__rregex)) } ;
    }


    template<
        typename ... regexs_t>
    constexpr auto
    operator > (
        and_<regexs_t...> const& __and,
        auto&& __rregex)
    {
        static_assert(is_regex_based(__rregex)) ;

        using namespace thodd::meta ;

        return 
        and_<regexs_t..., decay_t<decltype(__rregex)>>
        { __and.regexs + make_tuple(perfect<decltype(__rregex)>(__rregex)) } ;
    }
}

#endif