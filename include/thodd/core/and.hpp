#ifndef __THODD_META_AND_HPP__
#  define __THODD_META_AND_HPP__

namespace
thodd
{
    constexpr bool 
    and_c()
    {
        return true;
    }


    constexpr auto
    and_c(
        auto&& __v)
    {
        return 
        static_cast<decltype(__v)>(__v);
    }


    constexpr auto
    and_c(
        auto&& __v,
        auto&&... __vs)
    {
        return 
         static_cast<decltype(__v)>(__v) 
         && and_c( static_cast<decltype(__vs)>(__vs)...);
    }
}

#endif