#ifndef __THODD_META_TRAITS_ADD_CV_HPP__
#  define __THODD_META_TRAITS_ADD_CV_HPP__

namespace
thodd::meta
{
    constexpr auto const volatile
    add_cv(
        auto __t)
    {
        return __t;
    }
}

#endif