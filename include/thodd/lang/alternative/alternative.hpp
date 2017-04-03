#ifndef __THODD_LANG_ALTERNATIVE_HPP__
#  define __THODD_LANG_ALTERNATIVE_HPP__

#  include <thodd/tuple/tuple.hpp>
#  include <thodd/variant/variant.hpp>

#  include <thodd/core/declval.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/core/get.hpp>
#  include <thodd/core/between.hpp>

#  include <thodd/meta/traits/decay.hpp>

#  include <thodd/lang/core/core.hpp>
#  include <thodd/lang/core/regex.hpp>
#  include <thodd/lang/core/word.hpp> 

#  include <thodd/container/list.hpp>

namespace thodd::lang
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
        alternative<meta::decay_t<decltype(__cases)>...>
        { make_tuple(perfect<decltype(__cases)>(__cases)...) };
    }


    template<
        typename ... cases_t>
    constexpr auto 
    make_alternative(tuple<cases_t...> const& __cases)
    {
        return 
        alternative<meta::decay_t<cases_t>...>
        { __cases };
    }


        template<
        typename iterator_t, 
        typename subtoken_t>
    struct alternative_token
    {
        using range_t = thodd::detail::range<iterator_t>;

        range_t range;
        thodd::list<subtoken_t> subranges;
        size_t index;


        constexpr
        operator bool () const
        {
            return 
            thodd::between(
                subranges.size(), 
                min, max);
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
        typename subtoken_t>
    constexpr auto
    make_alternative_token(
        auto&& __begin, 
        auto&& __end, 
        thodd::list<subtoken_t> const& __subranges, 
        auto&& __index)
    {
        using iterator_t = meta::decay_t<decltype(__begin)>;

        return 
        alternative_token<iterator_t, subtoken_t>
        { thodd::range(
            perfect<decltype(__begin)>(__begin),
            perfect<decltype(__end)>(__end)),
            __subranges, 
            perfect<decltype(__index)>(__index) };
    }


    template<
        typename subtoken_t>
    constexpr auto
    make_alternative_token(
        auto&& __begin, 
        auto&& __end, 
        thodd::list<subtoken_t>&& __subranges, 
        auto&& __index)
    {
        using iterator_t = meta::decay_t<decltype(__begin)>;

        return 
        alternative_token<iterator_t, subtoken_t>
        { thodd::range(
            perfect<decltype(__begin)>(__begin),
            perfect<decltype(__end)>(__end)),
            thodd::rvalue(__subranges), 
            perfect<decltype(__index)>(__index) };
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

        thodd::foreach(
            __alter.algo.cases, 
            [&] (auto&& __case)
            {
                if(!__res) 
                    __res |= 
                        matches(
                            perfect<decltype(__case)>(__case), 
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
        auto list<>
        auto __save = __cursor;
        auto __index = 0u;

        thodd::foreach(
            __alter.algo.cases, 
            [&] (auto&& __case)
            {
                if(!((bool) __res)) 
                    __res = 
                        rvalue(
                            matches(
                                perfect<decltype(__case)>(__case), 
                                __cursor, 
                                __end));  
                
                if(!__res) 
                {
                    __cursor = __save;
                    ++__index;
                }
            });
        
        __res.index = __index;

        return make_alternative_token(__save, __cursor, , __index);
    }


    template<
        typename ... cases_t, 
        typename ... casters_t, 
        typename caster_t, 
        size_t ... indexes_c>
    inline auto 
    interpret(
        word<alternative<word<cases_t,  casters_t>...>, caster_t> const& __alter,
        auto&& __tree, 
        sequence<size_t, indexes_c...> const&)
    {
        return 
        thodd::make_tuple(
            interpret(
                thodd::get<indexes_c>(__alter.algo.cases), 
                __tree)...);
    }
    
    
    template<
        typename ... cases_t, 
        typename ... casters_t, 
        typename caster_t>
    inline auto 
    interpret(
        word<alternative<word<cases_t,  casters_t>...>, caster_t> const& __alter,
        auto&& __tree)
    {
        variant<meta::decay_t<
            decltype(
                interpret(
                    thodd::declval<word<cases_t,  casters_t>>(), 
                    __tree))>...> __var;

        auto __subtree_it = __tree.sub_begin(); 
        auto __index = 0u;

        
        thodd::foreach(
            __alter.algo.cases, 
            [&] (auto&& __case)
            {
                if(__subtree_it != __tree.sub_end() 
                   and (*__subtree_it).index == __index)
                    __var = interpret(__case, *__subtree_it);
                
                ++__subtree_it;
                ++__index;
            });
        
        return __alter.caster(__var);
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
                + make_tuple(__rregex)));
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

#endif