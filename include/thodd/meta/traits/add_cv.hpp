#ifndef __THODD_META_TRAITS_ADD_CV_HPP__
#  define __THODD_META_TRAITS_ADD_CV_HPP__

#  include <thodd/meta/type.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr type_<type_t const volatile>
    add_cv(
        type_<type_t> const&)
    {
        return {};
    }

    template<
        typename type_t>
    using add_cv_t = __type<decltype(add_cv(type_<type_t>{}))>;
}

#endif