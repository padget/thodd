#ifndef __THODD_LANG_FOLLOW_HPP__
#  define __THODD_LANG_FOLLOW_HPP__

#  include <thodd/tuple.hpp>
#  include <thodd/law.hpp>
#  include <thodd/variant.hpp>

#  include <thodd/lang_core.hpp>
#  include <thodd/lang_matcher.hpp>
#  include <thodd/lang_word.hpp> 

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
            word<follow<word<cases_t>...>> const& __alter, 
            auto& __cursor, 
            auto const& __end)
        {   
            list<decltype(token(0u, __cursor, __cursor))> __subranges;

            auto __save = __cursor;
            auto __continue = true;
            auto __index = 0u;

            __alter.algo.algos.template foreach(
                [&__continue, &__subranges, &__index, 
                 &__save, &__cursor, &__end] 
                (auto&& __case)
                {
                    using case_t = decltype(__case);

                    if(__continue)
                    {
                        auto __subrange = 
                            matches(perfect<case_t>(__case), __cursor, __end);

                        if((__continue = (bool) __subrange))
                        {
                            __subrange.index = __index;
                            thodd::push_back(__subranges, __subrange); 
                            ++__index;
                        }
                        else 
                        {  
                            __subranges.clear();
                            __cursor = __save;
                        }   
                    }     
                });
        
            return token(0u, __save, __cursor, __subranges);
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
            word<lalgo_t> const& __lword,
            word<ralgo_t> const& __rword )
        {
            return 
            make_word(
                make_follow(
                    __lword, 
                    __rword));   
        }

        
        template<
            typename ... lcases_t, 
            typename rcase_t>
        constexpr auto
        operator >> (
            word<follow<word<lcases_t>...>> const& __lalter,
            word<rcase_t> const& __rword)
        {
            return 
            make_word(
                make_follow(
                    __lalter.algo.algos 
                  + __rword));
        }


        template<
            typename ... lcases_t, 
            typename ... rcases_t>
        constexpr auto
        operator >> (
            word<follow<word<lcases_t>...>> const& __lalter,
            word<follow<word<rcases_t>...>> const& __ralter)
        {
            return 
            make_word(
                make_follow(
                    __lalter.algo.algos 
                  + __ralter.algo.algos));
        }
    }
}

#endif