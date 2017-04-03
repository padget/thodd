#ifndef __THODD_CORE_BEGIN_HPP__
#  define __THODD_CORE_BEGIN_HPP__

#  include <thodd/core/perfect.hpp>

namespace 
thodd
{
    constexpr auto
    begin(
        auto&& __o)
    -> decltype(auto)
    {
        return 
        perfect<decltype(__o)>(__o)
        .begin();
    }
}

#endif