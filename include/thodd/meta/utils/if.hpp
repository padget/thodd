#ifndef __THODD_META_UTILS_HPP__
#  define __THODD_META_UTILS_HPP__

namespace 
thodd::meta
{
    template<
        bool cond_c,
        typename then_t, 
        typename else_t>
    constexpr auto 
    if_( 
        type_<then_t> const&, 
        type_<else_t> const&)
    {
        if constexpr(cond_c) 
            return type_<then_t>{}; 
        else 
            return type_<else_t>{};
    }
}

#endif