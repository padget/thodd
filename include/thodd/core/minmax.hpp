#ifndef __THODD_CORE_MINMAX_HPP__
#  define __THODD_CORE_MINMAX_HPP__

#  include <thodd/core/expand.hpp>
#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/meta/type.hpp>
#  include <thodd/meta/traits/add_pointer.hpp>

namespace 
thodd
{
    constexpr auto 
    max(
        auto const& __index,
        auto const&... __indexes)
    -> decltype(auto)
    {
        using namespace meta;
        using decayed_ptr_t = 
            __type<decltype(
                add_pointer(
                    decay(__type<decltype(__index)>{})))>;

        decayed_ptr_t __res{&__index};
        expand((__res = *__res < __indexes ? &__indexes : __res)...);
        return *__res;
    }


    constexpr auto 
    min(
        auto&& __index,
        auto&&... __indexes)
    -> decltype(auto)
    {
        using namespace meta;
        using decayed_ptr_t = 
            __type<decltype(
                meta::add_pointer(
                    meta::decay(__type<decltype(__index)>{})))>;

        decayed_ptr_t __res{&__index};
        expand((__res = *__res < __indexes ? __res : &__indexes)...);
        return *__res;
    }
}

#endif 