#ifndef __THODD_LANG_FOLLOW_HPP__
#  define __THODD_LANG_FOLLOW_HPP__

#  include <thodd/tuple.hpp>
#  include <thodd/dynamic_tuple.hpp>
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
        typename iterator_t, 
        typename ... subtokens_t>
    struct follow_token
    {
        using range_t = thodd::detail::range<iterator_t>;

        range_t range;
        thodd::dynamic_tuple<subtokens_t...> subranges;

        constexpr
        operator bool () const
        {
            auto __res = true;

            thodd::foreach(
                subranges, 
                thodd::ref(__res) = 
                    thodd::cref(__res) 
                    && ($0 != val(nullptr)));

            if(__res)
                thodd::foreach(
                    subranges,
                    thodd::ref(__res) = 
                        thodd::cref(__res) 
                        && thodd::bind(thodd::cast_<bool>, *$0));

            return __res; 
        }

        inline auto const
        begin() const
        {
            return range.begin();
        }


        inline auto
        begin()
        {
            return range.begin();
        }


        inline auto const
        end() const
        {
            return range.end();
        }


        inline auto
        end()
        {
            return range.end();
        }


        inline auto const
        subbegin() const
        {
            return subranges.begin();
        }


        inline auto
        subbegin()
        {
            return subranges.begin();
        }


        inline auto const
        subend() const
        {
            return subranges.end();
        }


        inline auto
        subend()
        {
            return subranges.end();
        }
    };

    template<
        typename ... subtokens_t>
    constexpr auto 
    make_follow_token(
        auto&& __begin, 
        auto&& __end,
        thodd::dynamic_tuple<subtokens_t...>&& __subranges)
    {
        return 
        follow_token<
            meta::decay<decltype(__begin)>, 
            subtokens_t...>
        { { decltype(__begin)(__begin), 
            decltype(__end)(__end) }, 
          thodd::rvalue(__subranges) };
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

        thodd::foreach(
            __follow.algo.algos,
            [&__res, &__save, 
             &__cursor, &__end] 
            (auto&& __algo)
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
                meta::decay<
                    decltype(
                        matches(
                            declval<word<cases_t, casters_t>>(), 
                            __cursor, __end))>...>;
        
        auto __save = __cursor;
        auto __continue = true;
        subranges_t __subranges;

        thodd::foreach_join(
            __follow.algo.algos,
            [&__continue, &__save, &__cursor, &__end] 
            (auto&& __case, auto& __subrange)
            {
                using case_t = decltype(__case);
                using subrange_t = 
                    meta::remove_pointer<
                        meta::decay<decltype(__subrange)>>;

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
    
        return make_follow_token(__save, __cursor, thodd::rvalue(__subranges));
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
        /*tuple<meta::decay<
            decltype(interpret(thodd::declval<word<algos_t,  casters_t>>(), 
                     __tree))>...> __tpl;

        auto __subtree_it = __tree.sub_begin(); 

        thodd::foreach_join(__follow.algo.algos, 
            [&__subtree_it] 
            (auto&& __case, 
                auto&& __tpl_item)
            {
                __tpl_item = interpret(__case, *__subtree_it);
                ++__subtree_it;
            }, __tpl);
        
        return __follow.caster(__tpl);*/
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
                + make_tuple(__rregex)));
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
                + make_tuple(__rword)));
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