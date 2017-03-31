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
        then_t const&, 
        else_t const&)
    {
        if constexpr(cond_c) 
            return then_t{}; 
        else 
            return else_t{};
    }
}

#endif