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
#  include <thodd/tuple/dynamic_tuple.hpp>

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
        dynamic_tuple<meta::decay_t<
            decltype(
                matches(
                    thodd::declval<word<cases_t,  casters_t>>(), 
                    __cursor, __end))>...> __subranges;
       
        auto __save = __cursor;
        auto __index = 0u;
        auto __continue = true;

        thodd::foreach_join(
            [&] 
            (auto&& __case, 
             auto&& __subrange)
            {
                if(__continue) 
                {
                    auto&& __token = 
                        rvalue(
                            matches(
                                perfect<decltype(__case)>(__case), 
                                __cursor, 
                                __end)); 
                    
                    if(static_cast<bool>(__token))
                    {
                        __continue = !__continue;
                        __subrange = 
                            new meta::remove_pointer_t<
                                    meta::decay_t<
                                        decltype(__subrange)>>
                                (thodd::rvalue(__token));
                    }
                    else 
                    {
                        ++__index;
                        __cursor = __save;
                    }
                }
            },
            __alter.algo.cases, 
            __subranges);

        if(__save == __cursor)
            std::cout << "prout" << std::endl; 

        return make_alternative_token(__save, __cursor, __subranges, __index);
    }
}

#endif