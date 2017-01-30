#ifndef __THODD_LANG_SOME_HPP__
#  define __THODD_LANG_SOME_HPP__

#  include <thodd/tuple.hpp>
#  include <thodd/law.hpp>
#  include <thodd/variant.hpp>
#  include <thodd/containers.hpp>

#  include <thodd/lang_core.hpp>
#  include <thodd/lang_matcher.hpp>

namespace thodd
{
    namespace lang
    {
        template<
            typename something_t>
        struct some
        {
            something_t something;
            size_t min{0u}, 
                   max{1u};

            constexpr auto 
            operator()(
                size_t __min, 
                size_t __max) const
            {
                return 
                make_matcher(
                    some<something_t>
                    {something, __min, __max});
            }

            constexpr auto 
            operator()(
                size_t __minmax) const
            {
                return 
                make_matcher(
                    some<something_t>
                    {something, __minmax, __minmax});
            }
        };

        constexpr auto
        make_some(
            auto&& __something)
        {
            return 
            some<meta::decay<decltype(__something)>>
            {perfect<decltype(__something)>(__something)};
        }


        inline auto
        matches(
            matcher<some<matcher<auto>>> const& __some, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __cpt = 0u;

            while(matches(__some.algo.something, __cursor, __end))
                ++__cpt;

            return __some.algo.min <= __cpt 
                && __cpt <= __some.algo.max;
        }


        template<
            typename ... cases_t>
        inline auto 
        matches(
            rule<some<rule<cases_t>...>> const& __alter, 
            auto& __cursor, 
            auto const& __end)
        {              
            decltype(token(__cursor, __cursor)) __res;
            auto __save = __cursor;

            __alter.algo.cases.template foreach(
                [&__res, &__save, 
                 &__cursor, &__end] 
                (auto&& __case)
                {
                    if(!((bool) __res)) 
                        __res = matches(perfect<decltype(__case)>(__case), 
                                         __cursor, 
                                         __end);  
                    
                    if(!__res) 
                        __cursor = __save;
                });
        
            return __res;
        }
    }
}

#endif // !__THODD_LANG2_HPP__