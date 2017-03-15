#ifndef __THODD_META_TRAITS_IS_SAME_HPP_
#  define __THODD_META_TRAITS_IS_SAME_HPP_

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename first_t, 
        typename other_t>
    constexpr auto 
    is_same(
        type_<first_t> const&,
        type_<other_t> const&)
    {
        return false;
    }

    template<
        typename type_t>
    constexpr auto 
    is_same(
        type_<type_t> const&,
        type_<type_t> const&)
    {
        return true;
    }

    template<
        typename type_t>
    using is_samec_t = __type<decltype(is_same(type_<type_t>{}))>;
}

#endif