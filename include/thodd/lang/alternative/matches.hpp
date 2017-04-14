#ifndef __THODD_LANG_ALTERNATIVE_MATCHES_HPP__
#  define __THODD_LANG_ALTERNATIVE_MATCHES_HPP__

#  include <thodd/lang/core/regex.hpp>
#  include <thodd/lang/core/word.hpp>
#  include <thodd/lang/alternative/alternative.hpp>
#  include <thodd/lang/alternative/alternative_token.hpp>

#  include <thodd/core/perfect.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/declval.hpp>

#  include <thodd/tuple/functional.hpp>

namespace 
thodd::lang
{
    template<
        typename ... cases_t>
    inline auto 
    matches(
        regex<alternative<regex<cases_t>...>> const& __alter, 
        auto& __cursor, 
        auto const& __end)
    {
        auto __res = false;                
        auto __save = __cursor;

        thodd::foreach(
            __alter.algo.cases, 
            [&] (auto&& __case)
            {
                if(!__res) 
                    __res |= 
                        matches(
                            perfect<decltype(__case)>(__case), 
                            __cursor, 
                            __end);  
                
                if(!__res) 
                    __cursor = __save;
            });
    
        return __res;
    }


    template<
        typename ... cases_t, 
        typename ... casters_t, 
        typename caster_t>
    inline auto 
    matches(
        word<alternative<word<cases_t, casters_t>...>, caster_t> const& __alter, 
        auto& __cursor, 
        auto const& __end)
    {              
        variant<meta::decay_t<
            decltype(
                matches(
                    thodd::declval<word<cases_t,  casters_t>>(), 
                    __cursor, __end))>...> __var;
       
        auto __save = __cursor;
        auto __index = 0u;
        auto __continue = true;
       

        thodd::foreach(
            __alter.algo.cases, 
            [&] (auto&& __case)
            {
                if(__continue) 
                {
                    auto&& __tmp = 
                        rvalue(
                            matches(
                                perfect<decltype(__case)>(__case), 
                                __cursor, 
                                __end)); 

                    __continue = static_cast<bool>(__tmp);
                    
                    if(__continue)
                        __var = __tmp;
                }

                if(!__continue) 
                {
                    __cursor = __save;
                    ++__index;
                }
            });

        return make_alternative_token(__save, __cursor, __var, __index);
    }
}

#endif