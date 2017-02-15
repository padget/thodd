#ifndef __THODD_LANG_ALTERNATIVE_HPP__
#  define __THODD_LANG_ALTERNATIVE_HPP__

#  include<thodd/tuple.hpp>
#  include<thodd/law.hpp>
#  include<thodd/variant.hpp>

#  include<thodd/lang_core.hpp>
#  include <thodd/lang_regex.hpp>
#  include <thodd/lang_word.hpp> 

namespace thodd
{
    namespace lang
    {
        template<
            typename ... cases_t>
        struct alternative
        {
            tuple<cases_t...> cases;
        };


        constexpr auto 
        make_alternative(
            auto&&... __cases)
        {
            return 
            alternative<meta::decay<decltype(__cases)>...>
            {make_tuple(perfect<decltype(__cases)>(__cases)...)};
        }


        template<
            typename ... cases_t>
        constexpr auto 
        make_alternative(tuple<cases_t...> const& __cases)
        {
            return 
            alternative<meta::decay<cases_t>...>
            {__cases};
        }


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

            __alter.algo.cases.template foreach(
                [&__res, &__save, &__cursor, &__end] (auto&& __case)
                {
                    if(!__res) 
                        __res |= matches(perfect<decltype(__case)>(__case), 
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
            auto&& __res = token(0u, __cursor, __cursor);
            auto __save = __cursor;
            auto __index = 0u;

            __alter.algo.cases.template foreach(
                [&__res, &__save, &__index, 
                 &__cursor, &__end] 
                (auto&& __case)
                {
                   if(!((bool) __res)) 
                        __res = matches(perfect<decltype(__case)>(__case), 
                                         __cursor, 
                                         __end);  
                    
                    if(!__res) 
                    {
                        __cursor = __save;
                        ++__index;
                    }
                });
            
            __res.index = __index;

            return __res;
        }





        template<
            typename lcase_t, 
            typename rcase_t>
        constexpr auto
        operator | (
            regex<lcase_t> const& __lregex,
            regex<rcase_t> const& __rregex )
        {
            return 
            make_regex(
                make_alternative(
                    __lregex, 
                    __rregex));   
        }


        template<
            typename ... lcases_t, 
            typename rcase_t>
        constexpr auto
        operator | (
            regex<alternative<regex<lcases_t>...>> const& __lalter,
            regex<rcase_t> const& __rregex)
        {
            return 
            make_regex(
                make_alternative(
                    __lalter.algo.cases 
                  + __rregex));
        }


        template<
            typename ... lcases_t, 
            typename ... rcases_t>
        constexpr auto
        operator | (
            regex<alternative<regex<lcases_t>...>> const& __lalter,
            regex<alternative<regex<rcases_t>...>> const& __ralter)
        {
            return 
            make_regex(
                make_alternative(
                    __lalter.algo.cases 
                  + __ralter.algo.cases));
        }


        template<
            typename lcase_t, 
            typename lcaster_t,
            typename rcase_t, 
            typename rcaster_t>
        constexpr auto
        operator | (
            word<lcase_t, lcaster_t> const& __lword,
            word<rcase_t, rcaster_t> const& __rword)
        {
            return 
            make_word(
                make_alternative(
                    __lword, 
                    __rword));   
        }


        template<
            typename ... lalgos_t,
            typename ... lcasters_t,
            typename lcaster_t, 
            typename ralgo_t,
            typename rcaster_t>
        constexpr auto
        operator | (
            word<alternative<word<lalgos_t, lcasters_t>...>, lcaster_t> const& __lalter,
            word<ralgo_t, rcaster_t> const& __rword)
        {
            return 
            make_word(
                make_alternative(
                    __lalter.algo.algos 
                  + __rword));
        }

        template<
            typename ... lcases_t,
            typename ... lcasters_t,
            typename lcaster_t, 
            typename ... rcases_t,
            typename ... rcasters_t, 
            typename rcaster_t>
        constexpr auto
        operator | (
            word<alternative<word<lcases_t, lcasters_t>...>, lcaster_t> const& __lalter,
            word<alternative<word<rcases_t, rcasters_t>...>, rcaster_t> const& __ralter)
        {
            return 
            make_word(
                make_alternative(
                    __lalter.algo.cases 
                  + __ralter.algo.cases));
        }
    }
}

#endif