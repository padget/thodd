#ifndef __THODD_LANG_FOLLOW_HPP__
#  define __THODD_LANG_FOLLOW_HPP__

#  include <thodd/tuple.hpp>
#  include <thodd/law.hpp>
#  include <thodd/variant.hpp>

#  include <thodd/lang_core.hpp>
#  include <thodd/lang_matcher.hpp>
#  include <thodd/lang_rule.hpp> 

namespace thodd
{
    namespace lang
    {
        template<
            typename ... algos_t>
        struct follow
        {
            tuple<algos_t...> algos;
        };


        constexpr auto 
        make_follow(
            auto&&... __algos)
        {
            return 
            follow<meta::decay<decltype(__algos)>...>
            {make_tuple(perfect<decltype(__algos)>(__algos)...)};
        }


        template<
            typename ... algos_t>
        constexpr auto 
        make_follow(
            tuple<algos_t...> const& __algos)
        {
            return 
            follow<meta::decay<algos_t>...>
            {__algos};
        }


        template<
            typename ... algos_t>
        inline auto 
        matches(
            matcher<follow<matcher<algos_t>...>> const& __follow, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __res = true;
            auto __save = __cursor;

            __follow.algo.algos.template foreach(
                [&__res, &__save, &__cursor, &__end] (auto&& __algo)
                {
                    if(__res) 
                        __res &= matches(
                                    perfect<decltype(__algo)>(__algo),
                                    __cursor, 
                                    __end);
                });

            if(!__res)
                __cursor = __save;

            return __res;
        } 


        template<
            typename ... cases_t>
        inline auto 
        matches(
            rule<follow<rule<cases_t>...>> const& __alter, 
            auto& __cursor, 
            auto const& __end)
        {   
            list<decltype(token(__cursor, __cursor))> __subranges;

            auto __save = __cursor;
            auto __continue = true;

            __alter.algo.algos.template foreach(
                [&__continue, &__subranges, 
                 &__save, &__cursor, &__end] 
                (auto&& __case)
                {
                    using case_t = decltype(__case);

                    if(__continue)
                    {
                        auto __subrange = 
                            matches(perfect<case_t>(__case), __cursor, __end);

                        if((__continue = (bool) __subrange))
                            __subranges.push_at(__subrange, __subranges.end()); 
                        else 
                        {  
                            __subranges.clear();
                            __cursor = __save;
                        }   
                    }     
                });
        
            return token(__save, __cursor, __subranges);
        }

          template<
            typename lalgo_t, 
            typename ralgo_t>
        constexpr auto
        operator >> (
            matcher<lalgo_t> const& __lmatcher,
            matcher<ralgo_t> const& __rmatcher )
        {
            return 
            make_matcher(
                make_follow(
                    __lmatcher, 
                    __rmatcher));   
        }

         template<
            typename ... lcases_t, 
            typename rcase_t>
        constexpr auto
        operator >> (
            matcher<follow<matcher<lcases_t>...>> const& __lalter,
            matcher<rcase_t> const& __rmatcher)
        {
            return 
            make_matcher(
                make_follow(
                    __lalter.algo.algos 
                  + __rmatcher));
        }


        template<
            typename ... lcases_t, 
            typename ... rcases_t>
        constexpr auto
        operator >> (
            matcher<follow<matcher<lcases_t>...>> const& __lalter,
            matcher<follow<matcher<rcases_t>...>> const& __ralter)
        {
            return 
            make_matcher(
                make_follow(
                    __lalter.algo.algos 
                  + __ralter.algo.algos));
        }




        template<
            typename lalgo_t, 
            typename ralgo_t>
        constexpr auto
        operator >> (
            rule<lalgo_t> const& __lrule,
            rule<ralgo_t> const& __rrule )
        {
            return 
            make_rule(
                make_follow(
                    __lrule, 
                    __rrule));   
        }

        
        template<
            typename ... lcases_t, 
            typename rcase_t>
        constexpr auto
        operator >> (
            rule<follow<rule<lcases_t>...>> const& __lalter,
            rule<rcase_t> const& __rrule)
        {
            return 
            make_rule(
                make_follow(
                    __lalter.algo.algos 
                  + __rrule));
        }


        template<
            typename ... lcases_t, 
            typename ... rcases_t>
        constexpr auto
        operator >> (
            rule<follow<rule<lcases_t>...>> const& __lalter,
            rule<follow<rule<rcases_t>...>> const& __ralter)
        {
            return 
            make_rule(
                make_follow(
                    __lalter.algo.algos 
                  + __ralter.algo.algos));
        }
    }
}

#endif