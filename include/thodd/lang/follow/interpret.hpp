#ifndef __THODD_LANG_FOLLOW_INTERPRET_HPP__
#  define __THODD_LANG_FOLLOW_INTERPRET_HPP__

#  include <thodd/lang/core/word.hpp>
#  include <thodd/lang/follow/follow.hpp>

#  include <thodd/core/get.hpp>
#  include <thodd/core/declval.hpp> 

#  include <thodd/tuple/tuple.hpp> 
#  include <thodd/tuple/functional.hpp> 

#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::lang
{
    template<
        typename ... algos_t, 
        typename ... casters_t, 
        typename caster_t, 
        size_t ... indexes_c>
    inline auto 
    interpret(
        word<follow<word<algos_t,  casters_t>...>, caster_t> const& __follow,
        auto&& __tree, 
        sequence<size_t, indexes_c...> const&)
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
        /*tuple<meta::decay_t<
            decltype(interpret(declval<word<algos_t,  casters_t>>(), 
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
}

#endif