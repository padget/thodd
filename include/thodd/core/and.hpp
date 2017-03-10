#ifndef __THODD_META_AND_HPP__
#  define __THODD_META_AND_HPP__

namespace
thodd
{
    constexpr bool 
    and_()
    {
        return true;
    }


    constexpr auto
    and_(
        auto&& __v)
    {
        return 
        static_cast<decltype(__v)>(__v);
    }


    constexpr auto
    and_(
        auto&& __v,
        auto&&... __vs)
    {
        return 
         static_cast<decltype(__v)>(__v) 
         && and_( static_cast<decltype(__vs)>(__vs)...);
    }
}

#endif