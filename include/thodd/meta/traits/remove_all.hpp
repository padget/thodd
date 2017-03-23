#ifndef __THODD_META_TRAITS_REMOVE_ALL_HPP__
#  define __THODD_META_TRAITS_REMOVE_ALL_HPP__

#  include <thodd/meta/type.hpp>
#  include <thodd/meta/traits/remove_pointer.hpp>
#  include <thodd/meta/traits/remove_reference.hpp>
#  include <thodd/meta/traits/remove_cv.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    remove_all(
        type_<type_t> const&)
    {
        return 
        remove_reference(
            remove_cv(
                remove_pointer(
                    type_<type_t>{})));
    }

    template<
        typename type_t>
    using remove_all_t = __type<decltype(remove_all(type_<type_t>{}))>;
}

#endif