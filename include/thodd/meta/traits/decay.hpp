#ifndef __THODD_META_TRAITS_DECAY_HPP__
#  define __THODD_META_TRAITS_DECAY_HPP__

#  include <thodd/meta/traits/remove_cv.hpp>
#  include <thodd/meta/traits/remove_reference.hpp>
#  include <thodd/meta/type.hpp>

namespace
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    decay(
        type_<type_t> const&)
    {
        return 
        remove_reference(
            remove_cv(
                type_<type_t>{}));
    }
}

#endif