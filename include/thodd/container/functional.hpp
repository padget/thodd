#ifndef __THODD_CONTAINER_FUNC_HPP__
#  define __THODD_CONTAINER_FUNC_HPP__

#  include <thodd/core/perfect.hpp>
#  include <thodd/core/rvalue.hpp>

namespace 
thodd
{
    extern constexpr auto
    size = 
        [](auto const& __container)
        -> decltype(auto)
        {
            return 
            __container.size();
        };


    extern constexpr auto 
    push_at = 
        [](auto& __container, 
            auto&& __item, 
            auto const& __pos)
        -> decltype(auto)
        {
            return 
            __container.
            push_at(
                perfect<decltype(__item)>(__item), 
                __pos);
        };


    extern constexpr auto
    push_back = 
        [](auto& __container, 
            auto&& __item)
        -> decltype(auto)
        {
            return 
            push_at(
                __container, 
                perfect<decltype(__item)>(__item), 
                __container.end());
        };


    extern constexpr auto
    push_front =
        [](auto& __container, 
           auto&& __item)
        -> decltype(auto)
        {
            return 
            push_at(
                __container, 
                perfect<decltype(__item)>(__item), 
                __container.begin());
        };


    extern constexpr auto
    move_back = 
        [](auto& __container, 
            auto&& __item)
        -> decltype(auto)
        {
            return 
            push_at(
                __container, 
                rvalue(perfect<decltype(__item)>(__item)), 
                __container.end());
        };


    extern constexpr auto
    move_front = 
        [](auto& __container, 
        auto&& __item)
        -> decltype(auto)
        {
            return 
            push_at(
                __container, 
                rvalue(perfect<decltype(__item)>(__item)), 
                __container.begin());
        };


    extern constexpr auto 
    pop_at = 
        [](auto& __container, 
        auto const& __pos)
        -> decltype(auto)
        {
            return __container.pop_at(__pos);
        };


    extern constexpr auto
    pop_back = 
        [](auto& __container)
        -> decltype(auto)
        {
            return 
            pop_at(
                __container, 
                __container.end());
        };


    extern constexpr auto
    pop_front = 
        [](auto& __container)
        -> decltype(auto)
        {
            return 
            pop_at(
                __container, 
                __container.begin());
        };
}

#endif