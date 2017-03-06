#ifndef __THODD_CORE_MINMAX_HPP__
#  define __THODD_CORE_MINMAX_HPP__

#  include <thodd/core_expand.hpp>

namespace 
thodd
{
    constexpr auto 
    max(
        auto  __index,
        auto ... __indexes)
    {
        size_t __res{__index};
        expand((__res = __res < __indexes ? __indexes : __res)...);

        return __res;
    }


    


    constexpr auto 
    minof(
        auto const& __index,
        auto const&... __indexes)
    {
        size_t __res{__index};
        expand((__res = __res < __indexes ? __res : __indexes)...);

        return __res;
    }

    template<
        size_t ... indexes_c>
    constexpr auto 
    minof(
        sequence<indexes_c...>)
    {
        return 
        minof(
            size_t{indexes_c}...);
    }
}

#endif 