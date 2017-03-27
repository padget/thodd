#ifndef __THODD_CORE_PERFECT_HPP__
#  define __THODD_CORE_PERFECT_HPP__

#  include <thodd/meta/traits/remove_reference.hpp>
#  include <thodd/meta/traits/is_lvalue_reference.hpp>

namespace 
thodd
{ 
    template<
        typename type_t>
    constexpr type_t&& 
    perfect(
        meta::remove_reference_t<type_t>& __t) noexcept
    {
        return 
        static_cast<type_t&&>(__t);
    } 

    template<  
        typename type_t>
    constexpr type_t&& 
    perfect(
        meta::remove_reference_t<type_t>&& __t) noexcept
    {
        static_assert(
            !meta::is_lvalue_reference_t<type_t>::value,
            "Can not forward an rvalue as an lvalue.");
        
        return 
        static_cast<type_t&&>(__t);
    }     
}

#endif