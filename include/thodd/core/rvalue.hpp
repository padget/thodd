#ifndef __THODD_CORE_RVALUE_HPP__
#  define __THODD_CORE_RVALUE_HPP__

#  include <thodd/meta/traits/remove_reference.hpp>

namespace 
thodd
{
    template<
        typename type_t>
    constexpr meta::remove_reference_t<type_t>&&
    rvalue(
        type_t&& __arg) noexcept
    {
        using namespace meta;

        return 
        static_cast<meta::remove_reference_t<type_t>&&>(__arg);
    }
}

#endif