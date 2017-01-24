#ifndef __THODD_LANG_FOLLOW_HPP__
#  define __THODD_LANG_FOLLOW_HPP__

#  include<thodd/tuple.hpp>
#  include<thodd/law.hpp>
#  include<thodd/variant.hpp>

#  include<thodd/lang_new_core.hpp>

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
            matcher<follow<algos_t...>> const& __follow, 
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

                    return __res;
                });

            if(!__res)
                __cursor = __save;

            return __res;
        } 
    }
}

#endif // !__THODD_LANG2_HPP__