#ifndef __THODD_META_TRAITS_IS_SAME_HPP_
#  define __THODD_META_TRAITS_IS_SAME_HPP_

namespace 
thodd::meta
{
    constexpr auto 
    is_same(
        auto const&,
        auto const&)
    {
        return false;
    }

    template<
        typename ltype_t>
    constexpr auto 
    is_same(
        ltype_t const&,
        ltype_t const&)
    {
        return true;
    }
}

#endif