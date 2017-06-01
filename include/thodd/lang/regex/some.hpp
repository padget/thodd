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
    };


    template<
        typename algo_t>
    constexpr some<regex<algo_t>>
    make_some(
        regex<algo_t> const& __regex)
    {
        return
        { __regex } ;
    }


    template<
        typename algo_t>
    constexpr some<regex<algo_t>>
    make_some(
        regex<algo_t> const& __regex, 
        positive_t const& __min, 
        positive_t const& __max)
    {
        return
        { __regex , __min, __max } ;
    }


    template<
        typename algo_t>
    constexpr auto
    operator + (
        regex<algo_t> const& __regex)
    {   
        return 
        make_regex(
            make_some(__regex, 1, infinity)) ;
    }


    template<
        typename algo_t>
    constexpr auto
    operator * (
        regex<algo_t> const& __regex)
    {   
        return 
        make_regex(
            make_some(__regex, 0, infinity)) ;
    }


    template<
        typename algo_t>
    constexpr auto
    operator ~ (
        regex<algo_t> const& __regex)
    {
        return 
        make_some(__regex) ;
    }
}


#endif