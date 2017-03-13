#ifndef __THODD_CORE_GET_HPP__
#  define __THODD_CORE_GET_HPP__

#  include <thodd/core/perfect.hpp>
#  include <thodd/core/size_t.hpp>

namespace 
thodd
{
    template<
        size_t index_c>
    constexpr auto
    get(
        auto&& __t) 
    -> decltype(
        perfect<decltype(__t)>(__t)
        .template get<index_c>())
    {
        return 
        perfect<decltype(__t)>(__t)
        .template get<index_c>();
    }


    template<
        typename type_t>
    constexpr auto
    get(
        auto&& __t) 
    -> decltype(
        perfect<decltype(__t)>(__t)
        .template get<type_t>())
    {
        return 
        perfect<decltype(__t)>(__t)
        .template get<type_t>();
    }
}

#endif