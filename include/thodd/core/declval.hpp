#ifndef __THODD_CORE_DECLVAL_HPP__
#  define __THODD_CORE_DECLVAL_HPP__

#  include <thodd/meta/traits/add_rvalue_reference.hpp>

namespace 
thodd::declval_detail
{
    template<
        typename type_t>
    struct protector
    {
        static const bool __stop = false;
        static meta::add_rvalue_reference_t<type_t> __delegate();
    };
}

namespace 
thodd 
{
    template<
        typename type_t>
    inline meta::add_rvalue_reference_t<type_t>
    declval() noexcept
    {
        using namespace declval_detail;

        static_assert(
            protector<type_t>::__stop,
            "declval() must not be used!");
        
        return 
        protector<type_t>::
        __delegate();
    }
}

#endif