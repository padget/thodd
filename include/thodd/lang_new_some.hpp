#ifndef __THODD_LANG_SOME_HPP__
#  define __THODD_LANG_SOME_HPP__

#  include <thodd/tuple.hpp>
#  include <thodd/law.hpp>
#  include <thodd/variant.hpp>
#  include <thodd/containers.hpp>

#  include <thodd/lang_new_core.hpp>
#  include <thodd/lang_new_matcher.hpp>

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
            matcher<some<auto>> const& __some, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __cpt = 0u;

            while(matches(__some.algo.something, __cursor, __end))
                ++__cpt;

            return __some.algo.min <= __cpt 
                && __cpt <= __some.algo.max;
                
        }
    }
}

#endif // !__THODD_LANG2_HPP__