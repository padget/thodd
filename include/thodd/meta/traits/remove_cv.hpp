#ifndef __THODD_META_TRAITS_REMOVE_CV_HPP__
#  define __THODD_META_TRAITS_REMOVE_CV_HPP__

#  include <thodd/meta/traits/remove_const.hpp>
#  include <thodd/meta/traits/remove_volatile.hpp>
#  include <thodd/meta/type.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    remove_cv(
        type_<type_t> const&)
    {
        return
        remove_const(
            remove_volatile(
                type_<type_t>{}));
    }

    template<
        typename type_t>
    using remove_cv_t = __type<decltype(remove_cv(type_<type_t>{}))>;
}

#endif