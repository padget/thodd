#ifndef __THODD_LANG_WORD_HPP__
#  define __THODD_LANG_WORD_HPP__

#  include <thodd/functional/functional.hpp>

#  include <thodd/core/exception.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/meta/traits/decay.hpp>

#  include <thodd/lang/core/token.hpp>
#  include <thodd/lang/core/regex.hpp>

namespace thodd::lang
{
    template<
        typename enum_t, 
        enum_t enum_c, 
        typename algo_t>
    struct word
    {
        algo_t algo ;
    } ;


    constexpr auto 
    make_word(
        auto&& __enum,
        auto&& __algo)
    {
        using algo_t = decltype(__algo) ;
        using enum_t = decltype(__enum) ;

        return 
        word<
            meta::decay_t<enum_t>, 
            __enum,
            meta::decay_t<algo_t>>
        { perfect<algo_t>(__algo) } ;
    }
}

#endif