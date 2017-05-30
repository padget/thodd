#ifndef __THODD_LANG_REGEX_MATCHES_HPP__
#  define __THODD_LANG_REGEX_MATCHES_HPP__



namespace 
thodd::lang::regex
{
    template<  
        typename algo_t>
    inline auto 
    matches(
        regex<algo_t> const& __regex, 
        auto& __cursor, 
        auto const& __end)
    {
        auto __res = false;
        
        if (__cursor != __end)
            __res = __regex.algo(__cursor, __end);

        return __res;
    }
    
}

#endif