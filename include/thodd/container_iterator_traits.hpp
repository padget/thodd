#ifndef __THODD_CONTAINER_ITERATOR_TRAITS_HPP__
#  define __THODD_CONTAINER_ITERATOR_TRAITS_HPP__

namespace thodd
{

    
    template<
        typename iterator_t>
    struct iterator_traits
    {
        using value_type = typename iterator_t::value_type;
    };


    template<
        typename type_t>
    struct iterator_traits <type_t*>
    {
        using value_type = type_t;
    };


    template<
        typename type_t>
    struct iterator_traits <type_t const*>
    {
        using value_type = type_t;
    };
}

#endif