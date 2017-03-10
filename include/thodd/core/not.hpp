#ifndef __THODD_META_NOT_HPP__
#  define 

namespace 
thodd
{
    constexpr auto
    not_(
        auto&& __v)
    {
        return 
        ! static_cast<decltype(__v)>(__v);
    }
}

#endif