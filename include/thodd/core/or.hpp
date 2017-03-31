#ifndef __THODD_META_OR_HPP__
#  define __THODD_META_OR_HPP__

namespace
thodd
{
    constexpr auto 
    or_c()
    {
        return false;
    }
    

    constexpr auto
    or_c(
        auto&& __v)
    {
        return __v;
    }


    constexpr auto
    or_c(
        auto&& __v,
        auto&&... __vs)
    {
        return 
        static_cast<decltype(__v)>(__v)  
        || or_c(static_cast<decltype(__vs)>(__vs)...);
    }

}

#endif 