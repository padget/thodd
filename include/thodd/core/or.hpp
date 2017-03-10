#ifndef __THODD_META_OR_HPP__
#  define __THODD_META_OR_HPP__

namespace
thodd
{
    constexpr auto 
    or_()
    {
        return false;
    }
    

    constexpr auto
    or_(
        auto&& __v)
    {
        return __v;
    }


    constexpr auto
    or_(
        auto&& __v,
        auto&&... __vs)
    {
        return 
        static_cast<decltype(__v)>(__v)  
        || or_(static_cast<decltype(__vs)>(__vs)...);
    }

}

#endif 