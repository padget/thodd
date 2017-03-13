#ifndef __THODD_CORE_SET_HPP__
#  define __THODD_CORE_SET_HPP__

#  include <thodd/core/perfect.hpp>

namespace 
thodd
{
    template<
        size_t index_c>
    constexpr auto
    set(
        auto&& __t, 
        auto&& __s) 
    -> decltype(
        perfect<decltype(__t)>(__t)
        .template set<index_c>(
            perfect<decltype(__s)>(__s)))
    {
        return 
        perfect<decltype(__t)>(__t)
        .template set<index_c>(
            perfect<decltype(__s)>(__s));
    }


    template<
        typename type_t>
    constexpr auto
    set(
        auto&& __t, 
        auto&& __s) 
    -> decltype(
        perfect<decltype(__t)>(__t)
        .template set<type_t>(
            perfect<decltype(__s)>(__s)))
    {
        return 
        perfect<decltype(__t)>(__t)
        .template set<type_t>(
            perfect<decltype(__s)>(__s));
    }
}

#endif