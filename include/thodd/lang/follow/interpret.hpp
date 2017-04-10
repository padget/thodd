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
                *thodd::get<indexes_c>(__tree))...);
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
        auto&& __res = 
        interpret(
            __follow, 
            perfect<decltype(__tree)>(__tree),
            make_sequence_t<size_t, 0, sizeof...(algos_t) - 1>{});

        return 
        __follow.caster(__res);
    }
}

#endif