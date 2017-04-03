#ifndef __THODD_LANG_FOLLOW_MATCHES_HPP__
#  define __THODD_LANG_FOLLOW_MATCHES_HPP__

#  include <thodd/lang/core/regex.hpp>
#  include <thodd/lang/follow/follow.hpp>
#  include <thodd/lang/follow/follow_token.hpp>
#  include <thodd/lang/core/word.hpp>

#  include <thodd/core/between.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/core/declval.hpp>

#  include <thodd/meta/traits/decay.hpp>

#  include <thodd/container/list.hpp>
#  include <thodd/container/functional.hpp>


namespace
thodd::lang
{
    template<
        typename ... algos_t>
    inline auto 
    matches(
        regex<follow<regex<algos_t>...>> const& __follow, 
        auto& __cursor, 
        auto const& __end)
    {
        auto __res = true;
        auto __save = __cursor;

        thodd::foreach(
            __follow.algo.algos,
            [&] (auto&& __algo)
            {
                if(__res) 
                    __res &= 
                    matches(
                        perfect<decltype(__algo)>(__algo),
                        __cursor, 
                        __end);
            });

        if(!__res)
            __cursor = __save;

        return __res;
    } 


    template<
        typename ... cases_t, 
        typename ... casters_t, 
        typename caster_t>
    inline auto 
    matches(
        word<follow<word<cases_t, casters_t>...>, caster_t> const& __follow, 
        auto& __cursor, 
        auto const& __end)
    {   
        using subranges_t = 
            thodd::dynamic_tuple<
                meta::decay_t<
                    decltype(
                        matches(
                            declval<word<cases_t, casters_t>>(), 
                            __cursor, __end))>...>;
        
        auto __save = __cursor;
        auto __continue = true;
        subranges_t __subranges;

        thodd::foreach_join(
            __follow.algo.algos,
            [&] (
                auto&& __case, 
                auto& __subrange)
            {
                using case_t = decltype(__case);
                using subrange_t = 
                    meta::remove_pointer_t<
                        meta::decay_t<decltype(__subrange)>>;

                if(__continue)
                {
                    __subrange = 
                        new subrange_t(
                            thodd::rvalue(
                                matches(
                                    perfect<case_t>(__case), 
                                    __cursor, 
                                    __end)));

                    if(!(__continue &= (bool) __subrange)) 
                        __cursor = __save;
                }     
            }, 
            __subranges);

        if(!__continue)
            thodd::foreach(
                __subranges, 
                thodd::delete_);
    
        return 
        make_follow_token(
            __save, 
            __cursor, 
            thodd::rvalue(__subranges));
    }
}

#endif