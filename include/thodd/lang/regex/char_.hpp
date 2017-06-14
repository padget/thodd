#ifndef __THODD_LANG_REGEX_CHAR_HPP__
#  define __THODD_LANG_REGEX_CHAR_HPP__ 

#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/lang/regex/regex.hpp>

namespace 
thodd::lang::regex 
{
    template<
        typename char_t>
    struct char_ : regex
    {
        char_t c ;

        constexpr char_(
            auto&& __c) :
            c { perfect<decltype(__c)>(__c) } {}
    } ;

    
    
    constexpr auto
    is_char(
        auto const&)
    {
        return false ;   
    }


    constexpr auto
    is_char(
        char_<auto> const&)
    {
        return true ;   
    }

    constexpr auto
    chr(auto&& __c)
    {
        using namespace thodd::meta;
        
        return 
        char_<decay_t<decltype(__c)>>
        { perfect<decltype(__c)>(__c) } ;
    }

    constexpr auto
    matches(
        char_<auto> const& __rx,
        auto& __current, 
        auto const& __end)
    {
        auto&& __matched = __current != __end 
                        && *__current == __rx.c ;
        ++__current ;
        return __matched ; 
    }
}

#endif