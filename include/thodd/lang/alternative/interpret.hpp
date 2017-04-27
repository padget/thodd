#ifndef __THODD_LANG_ALTERNATIVE_INTERPRET_HPP__
#  define __THODD_LANG_ALTERNATIVE_INTERPRET_HPP__

#  include <thodd/lang/core/word.hpp>
#  include <thodd/lang/alternative/alternative.hpp>

#  include <thodd/core/sequence.hpp>
#  include <thodd/core/size_t.hpp>
#  include <thodd/core/get.hpp>
#  include <thodd/core/declval.hpp>

#  include <thodd/tuple/tuple.hpp>
#  include <thodd/tuple/dynamic_tuple.hpp>
#  include <thodd/tuple/functional.hpp>

// #  include <thodd/variant/variant.hpp>

#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::lang
{
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
        dynamic_tuple<meta::decay_t<
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
}

#endif