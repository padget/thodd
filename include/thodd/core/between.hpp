#ifndef __THODD_CORE_BETWEEN_HPP__
#  define __THODD_CORE_BETWEEN_HPP__

namespace 
thodd
{
    constexpr auto 
    between(
        auto const& __value, 
        auto const& __min, 
        auto const& __max)
    {
        return __min <= __value
            && __value <= __max;
    }
}

#endif