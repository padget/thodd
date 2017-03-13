#ifndef __THODD_CORE_RVALUE_HPP__
#  define __THODD_CORE_RVALUE_HPP__

#  include <thodd/meta/traits/remove_reference.hpp>

namespace 
thodd
{
    constexpr auto
    rvalue(
        auto&& __arg) noexcept
    -> decltype(auto)
    {
        using namespace meta;

        using target_t = 
            remove_reference_t<
                decltype(__arg)>;

        return 
        static_cast<target_t&&>
        (__arg);
    }
}

#endif