#ifndef __THODD_LANG_SOME_INTERPRET_HPP__
#  define __THODD_LANG_SOME_INTERPRET_HPP__

#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/container/list.hpp>
#  include <thodd/container/functional.hpp>

namespace 
thodd::lang
{
    template<
        typename something_t, 
        typename caster_t, 
        typename some_caster_t>
    inline auto 
    interpret(
        word<some<word<something_t,  caster_t>>, some_caster_t> const& __some,
        auto&& __tree)
    {
        using target_t = 
            decltype(
                interpret(
                    __some.algo.something, 
                    *__tree.subbegin()));

        thodd::list<meta::decay_t<target_t>> __lst;

        for(auto const& __tk : __tree.subranges)
            thodd::push_back(
                __lst, 
                thodd::rvalue(interpret(__some.algo.something, __tk)));

        return 
        __some.caster(__lst);
    }
}

#endif