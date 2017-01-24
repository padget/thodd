#ifndef __THODD_LANG_ALTERNATIVE_HPP__
#  define __THODD_LANG_ALTERNATIVE_HPP__

#  include<thodd/tuple.hpp>
#  include<thodd/law.hpp>
#  include<thodd/variant.hpp>

#  include<thodd/lang_new_core.hpp>

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
            matcher<alternative<cases_t...>> const& __alter, 
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

                    return __res;
                });
        
            return __res;
        }
    }
}

#endif // !__THODD_LANG2_HPP__