#ifndef __THODD_LANG_REGEX_NOT_HPP__
#  define __THODD_LANG_REGEX_NOT_HPP__

#  include <thodd/lang/regex/regex.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::lang::regex 
{
    template<
        typename regex_t>
    struct not_ : regex
    {
        regex_t expr ;
    } ;

    
    constexpr auto
    operator ! (
        auto&& __regex)
    {
        static_assert(is_regex_based(__regex)) ;

        using namespace thodd::meta;

        return
        not_<decay_t<delctype(__regex)>>
        { perfect<delctype(__regex)>(__regex) } ; 
    }
}

#endif