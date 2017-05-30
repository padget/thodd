#ifndef __THODD_LANG_REGEX_SOME_HPP__
#  define __THODD_LANG_REGEX_SOME_HPP__

#  include <thodd/core/positive_t.hpp>
#  include <thodd/lang/regex/regex.hpp>
#  include <thodd/core/infinity.hpp>

namespace 
thodd::lang::regex
{
    template<
        typename regex_t>
    struct some
    {
        regex_t regex ;

        positive_t min {0} ;
        positive_t max {1} ; 
    };


    template<
        typename algo_t>
    constexpr some<regex<algo_t>>
    operator + (
        regex<algo_t> const& __regex)
    {   
        return 
        { __regex, 1, infinity } ;
    }


    template<
        typename algo_t>
    constexpr some<regex<algo_t>>
    operator * (
        regex<algo_t> const& __regex)
    {   
        return 
        { __regex, 0, infinity } ;
    }
}


#endif