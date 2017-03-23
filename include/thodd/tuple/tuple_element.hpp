#ifndef __THODD_TUPLE_ELEMENT_HPP__
#  define __THODD_TUPLE_ELEMENT_HPP__

#  include <thodd/core/perfect.hpp>
#  include <thodd/core/rvalue.hpp>

namespace thodd
{
    template<
        typename item_t,
        size_t index_c>
    struct tuple_element
    {
        item_t item;

        constexpr tuple_element() = default;

        explicit constexpr
        tuple_element(
            auto&& __oitem):
            item{ thodd::perfect<decltype(__oitem)>(__oitem) } {}
    };


    template<
        size_t index_c,
        typename item_t>
    constexpr item_t&
    get(
        tuple_element<item_t, index_c>& __pod)
    {
        return 
        __pod.item;
    }


    template<
        size_t index_c,
        typename item_t>
    constexpr item_t const&
    get(
        tuple_element<item_t, index_c> const& __pod)
    {
        return 
        __pod.item;
    }


    template<
        size_t index_c,
        typename item_t>
    constexpr item_t&&
    get(
        tuple_element<item_t, index_c>&& __pod)
    {
        return 
        rvalue(__pod.item);
    }
}


#endif