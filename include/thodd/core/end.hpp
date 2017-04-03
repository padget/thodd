#ifndef __THODD_CORE_END_HPP__
#  define __THODD_CORE_END_HPP__

#  include <thodd/core/perfect.hpp>

namespace 
thodd
{
    constexpr auto
    end(
        auto&& __o)
    -> decltype(auto)
    {
        return 
        perfect<decltype(__o)>(__o)
        .end();
    }
}

#endif