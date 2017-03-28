#ifndef __THODD_TUPLE_FUNCTIONAL_HPP__
#  define __THODD_TUPLE_FUNCTIONAL_HPP__

#  include <thodd/core/perfect.hpp>

namespace thodd
{
    constexpr auto
    apply(
        auto&& __t,
        auto&& __func)
    -> decltype(auto)
    {
        return 
        perfect<decltype(__t)>(__t)
        .template 
         apply(
            perfect<decltype(__func)>(__func));
    }


    constexpr auto
    functional_apply(
        auto&& __t,
        auto&& __func,
        auto&&... __args)
    -> decltype(auto)
    {        
        return 
        perfect<decltype(__t)>(__t)
        .template
         functional_apply(
            perfect<decltype(__func)>(__func), 
            perfect<decltype(__args)>(__args)...);   
    }


    constexpr auto
    foreach(
        auto&& __t,
        auto&& __func)
    -> decltype(auto)
    {
        return 
        perfect<decltype(__t)>(__t)
        .template
         foreach(
            perfect<decltype(__func)>(__func));
    }


    constexpr auto
    foreach_join(
        auto&& __t,
        auto&& __func,
        auto&& __tuple1)
    -> decltype(auto)
    {
        return 
        perfect<decltype(__t)>(__t)
        .template 
         foreach_join(
            perfect<decltype(__func)>(__func),
            perfect<decltype(__tuple1)>(__tuple1));
    }


    template<
        size_t from_c, 
        size_t to_c>
    constexpr auto
    extract(
        auto&& __t)
    -> decltype(auto)
    {
        return 
        perfect<decltype(__t)>(__t)
        .template
         extract<from_c, to_c>();
    }
}

#endif