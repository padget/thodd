#ifndef __THODD_LANG_REGEX_CHAR_HPP__
#  define __THODD_LANG_REGEX_CHAR_HPP__ 

#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/core/perfect.hpp>

namespace 
thodd::lang::regex 
{
    template<
        typename char_t>
    struct char_ : regex
    {
        char_t c;
    } ;

    template<
        typename type_t>
    constexpr auto
    is_char(
        type_t&&)
    {
        return 
        false ;   
    }
    
    template<
        typename type_t>
    constexpr auto
    is_char(
        char_<type_t> const&)
    {
        return 
        true ;   
    }

    constexpr auto
    chr(auto&& __c)
    {
        using namespace thodd::meta;

        return 
        char_<decay_t<decltype(__c)>>
        { perfect<decltype(__c)>(__c) } ;
    }
}

#endif