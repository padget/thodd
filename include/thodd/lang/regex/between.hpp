#ifndef __THODD_LANG_REGEX_BETWEEN_HPP__
#  define __THODD_LANG_REGEX_BETWEEN_HPP__

#  include <thodd/lang/regex/regex.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::lang::regex 
{
    template<
        typename min_t, 
        typename max_t>
    struct between : regex
    {
        min_t min ;  
        max_t max ;
    } ;


    constexpr auto
    operator - (
        auto&& __min, 
        auto&& __max)
    {
        static_assert(is_char(__min));
        static_assert(is_char(__max));

        using namespace thodd::meta;

        return
        between<
            decay_t<decltype(__min)>, 
            decay_t<decltype(__max)>> 
        { perfect<decltype(__min)>(__min), 
          perfect<decltype(__max)>(__max) } ;
    }
}

#endif 