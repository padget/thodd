#ifndef __THODD_LANG_SOME_MATCHES_HPP__
#  define __THODD_LANG_SOME_MATCHES_HPP__

#  include <thodd/lang/core/regex.hpp>
#  include <thodd/lang/some/some.hpp>
#  include <thodd/lang/core/word.hpp>

#  include <thodd/core/between.hpp>
#  include <thodd/core/rvalue.hpp>

#  include <thodd/container/list.hpp>
#  include <thodd/container/functional.hpp>

namespace 
thodd::lang
{
    template<
        typename something_t>
    inline auto
    matches(
        regex<some<regex<something_t>>> const& __some, 
        auto& __cursor, 
        auto const& __end)
    {
        auto __cpt = 0u;

        while(matches(__some.algo.something, __cursor, __end))
            ++__cpt;

        return 
        thodd::between(
            __cpt, 
            __some.algo.min,
            __some.algo.max);
    }


    template<
        typename something_t,
        typename caster_t, 
        typename some_caster_t>
    inline auto 
    matches(
        word<some<word<something_t,  caster_t>>, some_caster_t> const& __some, 
        auto& __cursor, 
        auto const& __end)
    {     
        using subtoken_t = 
            meta::decay_t<
                decltype(
                    matches(
                        __some.algo.something, 
                        __cursor, __end))>;

        auto __save = __cursor;            
        auto __cpt  = 0u;

        subtoken_t __subrange;
        thodd::list<subtoken_t> __subranges;
        
        while((__subrange = rvalue(matches(__some.algo.something, __cursor, __end))) 
            && __cpt <= __some.algo.max)
        {
            thodd::push_back(
                __subranges, 
                thodd::rvalue(__subrange));
            
            ++__cpt;
        }

        
        if(!thodd::between(
            __cpt, 
            __some.algo.min, 
            __some.algo.max))
        {    
            __subranges.clear();
            __cursor = __save;
        }

        return 
        make_some_token(
            __save, __cursor, 
            thodd::rvalue(__subranges), 
            __some.algo.min,
            __some.algo.max);
    }
}

#endif