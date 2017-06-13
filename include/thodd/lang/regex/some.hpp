#ifndef __THODD_LANG_REGEX_SOME_HPP__
#  define __THODD_LANG_REGEX_SOME_HPP__

#  include <thodd/core/positive_t.hpp>
#  include <thodd/lang/regex/regex.hpp>
#  include <thodd/core/infinity.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::lang::regex
{
    template<
        typename regex_t>
    struct some : regex
    {
        regex_t reg ;

        mutable positive_t min {0} ;
        mutable positive_t max {1} ; 
        
        constexpr some(auto&& __reg) :
            reg { __reg } {} 

        constexpr some
        operator () (
            positive_t const& __min, 
            positive_t const& __max) const
        {
            min = __min ;
            max = __max ;
            
            return 
            *this ;
        }
    } ;


    constexpr auto
    operator + (
        auto&& __regex)
    {   
        static_assert(is_regex_based(__regex)) ;

        using namespace thodd::meta ;

        return
        some<decay_t<decltype(__regex)>>
        { perfect<decltype(__regex)>(__regex) }(1, infinity) ;
    }

   
    constexpr auto
    operator * (
        auto&& __regex)
    {   
        static_assert(is_regex_based(__regex)) ;

        using namespace thodd::meta ;

        return
        some<decay_t<decltype(__regex)>>
        { perfect<decltype(__regex)>(__regex) }(1, infinity) ;
    }

        
    constexpr auto
    operator ~ (
        auto&& __regex)
    {   
        static_assert(is_regex_based(__regex)) ;

        using namespace thodd::meta ;
        
        return
        some<decay_t<decltype(__regex)>>
        { perfect<decltype(__regex)>(__regex) } ;
    }
}


#endif