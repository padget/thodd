#ifndef __THODD_CORE_PERFECT_HPP__
#  define __THODD_CORE_PERFECT_HPP__

#  include <thodd/meta/traits/remove_reference.hpp>

namespace 
thodd
{
    constexpr auto 
    perfect(
        auto&& __t) noexcept
    -> decltype(auto)
    {
        return 
        static_cast<
            decltype(__t)&&>
        (__t);
    }     
}

#endif