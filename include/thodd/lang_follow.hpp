#ifndef __THODD_LANG_FOLLOW_HPP__
#  define __THODD_LANG_FOLLOW_HPP__

#  include <thodd/tuple.hpp>
#  include <thodd/law.hpp>
#  include <thodd/variant.hpp>

#  include <thodd/lang_core.hpp>
#  include <thodd/lang_regex.hpp>
#  include <thodd/lang_word.hpp> 

namespace thodd::lang
{
    template<
        typename ... algos_t>
    struct follow
    {
        tuple<algos_t...> algos;
    };

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
        regex<follow<regex<algos_t>...>> const& __follow, 
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
        typename ... cases_t, 
        typename ... casters_t, 
        typename caster_t>
    inline auto 
    matches(
        word<follow<word<cases_t, casters_t>...>, caster_t> const& __follow, 
        auto& __cursor, 
        auto const& __end)
    {   
        list<decltype(token(false, 0u, __cursor, __cursor))> __subranges;

        auto __save = __cursor;
        auto __continue = true;
        auto __index = 0u;

        thodd::foreach(__follow.algo.algos,
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
                        thodd::push_back(__subranges, thodd::rvalue(__subrange)); 
                        ++__index;
                    }
                    else 
                    {  
                        __subranges.clear();
                        __cursor = __save;
                    }   
                }     
            });
    
        return token(__continue, 0u, __save, __cursor, thodd::rvalue(__subranges));
    }


        template<
        typename ... algos_t, 
        typename ... casters_t, 
        typename caster_t, 
        size_t ... indexes_c>
    inline auto 
    interpret(
        word<follow<word<algos_t,  casters_t>...>, caster_t> const& __follow,
        auto&& __tree, 
        indexes<indexes_c...> const&)
    {
        return 
        thodd::make_tuple(
            interpret(
                thodd::get<indexes_c>(__follow.algo.algos), 
                __tree)...);
    }
    
    template<
        typename ... algos_t, 
        typename ... casters_t, 
        typename caster_t>
    inline auto 
    interpret(
        word<follow<word<algos_t,  casters_t>...>, caster_t> const& __follow,
        auto&& __tree)
    {
            tuple<meta::decay<
                decltype(
                    interpret(
                        thodd::declval<word<algos_t,  casters_t>>(), 
                        __tree))>...> __tpl;

        auto __subtree_it = __tree.sub_begin(); 

        __follow.algo.algos.template foreach_join(
            [&__subtree_it] 
            (auto&& __case, 
                auto&& __tpl_item)
            {
                __tpl_item = interpret(__case, *__subtree_it);
                ++__subtree_it;
            }, __tpl);
        
        return __follow.caster(__tpl);
    }


    template<
        typename lalgo_t, 
        typename ralgo_t>
    constexpr auto
    operator >> (
        regex<lalgo_t> const& __lregex,
        regex<ralgo_t> const& __rregex )
    {
        return 
        make_regex(
            make_follow(
                make_tuple(
                    __lregex, 
                    __rregex)));   
    }

        template<
        typename ... lcases_t, 
        typename rcase_t>
    constexpr auto
    operator >> (
        regex<follow<regex<lcases_t>...>> const& __lfollow,
        regex<rcase_t> const& __rregex)
    {
        return 
        make_regex(
            make_follow(
                __lfollow.algo.algos 
                + __rregex));
    }


    template<
        typename ... lcases_t, 
        typename ... rcases_t>
    constexpr auto
    operator >> (
        regex<follow<regex<lcases_t>...>> const& __lfollow,
        regex<follow<regex<rcases_t>...>> const& __rfollow)
    {
        return 
        make_regex(
            make_follow(
                __lfollow.algo.algos 
                + __rfollow.algo.algos));
    }




    template<
        typename lalgo_t,
        typename lcaster_t, 
        typename ralgo_t,
        typename rcaster_t>
    constexpr auto
    operator >> (
        word<lalgo_t, lcaster_t> const& __lword,
        word<ralgo_t, rcaster_t> const& __rword )
    {
        return 
        make_word(
            make_follow(
                make_tuple(
                    __lword, 
                    __rword)));   
    }

    
    template<
        typename ... lcases_t, 
        typename ... lcasters_t,
        typename lcaster_t,
        typename rcase_t, 
        typename rcaster_t>
    constexpr auto
    operator >> (
        word<follow<word<lcases_t, lcasters_t>...>, lcaster_t> const& __lfollow,
        word<rcase_t, rcaster_t> const& __rword)
    {
        return 
        make_word(
            make_follow(
                __lfollow.algo.algos 
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
    operator >> (
        word<follow<word<lcases_t, lcasters_t>...>, lcaster_t> const& __lfollow,
        word<follow<word<rcases_t, rcasters_t>...>, rcaster_t> const& __rfollow)
    {
        return 
        make_word(
            make_follow(
                __lfollow.algo.algos 
                + __rfollow.algo.algos));
    }

}

#endif