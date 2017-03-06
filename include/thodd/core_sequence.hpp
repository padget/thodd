#ifndef __THODD_META_SEQUENCE_HPP__
#  define __THODD_META_SEQUENCE_HPP__

#  include <thodd/core_expand.hpp>
#  include <thodd/core_minmax.hpp>

namespace
thodd
{
    template<
        size_t max_c>
    struct upperbound {};


    template<
        size_t min_c>
    struct lowerbound {};


    template<
        size_t ... idxs_c>
    struct sequence {};    
}

namespace 
thodd::sequence_detail
{
    constexpr auto
    at_c(    
        size_t __index, 
        auto __item)
    {
        return __item;
    }


    constexpr auto
    at_c(
        size_t __index, 
        auto __item,
        auto __next, 
        auto ... __items)
    {
        return 
        __index == 0 ? 
        __item : 
        at_c(
            __index - 1, 
            __next, 
            __items...); 
    }


    template<
        size_t min_c, 
        size_t max_c, 
        size_t ... nexts_c>
    constexpr sequence<max_c, nexts_c...> 
    make_sequence(
        lowerbound<min_c>,
        upperbound<max_c>,
        sequence<max_c, nexts_c...>,
        auto __step)
    {
        return {};
    }


    template<
        size_t min_c, 
        size_t max_c, 
        size_t index_c,
        size_t ... nexts_c>
    constexpr auto 
    make_sequence(
        lowerbound<min_c>, 
        upperbound<max_c>, 
        sequence<index_c, nexts_c...>, 
        auto __step)
    {
        return 
        make_sequence(
            lowerbound<min_c>{}, 
            upperbound<max_c>{}, 
            sequence<__step(index_c), index_c, nexts_c...>{}, 
            __step);
    }

    template<
        size_t ... indexes_c>
    constexpr sequence<(sizeof(indexes_c) - 1 - indexes_c)...>
    simple_reverse_sequence(
        sequence<indexes_c...>)
    {
        return {};
    }
}


namespace 
thodd
{
    template<
        size_t ... indexes_c>
    constexpr auto 
    max(
        sequence<indexes_c...>)
    {
        return 
        thodd::max(
            size_t{indexes_c}...);
    }




    template<
        size_t ... indexes_c>
    constexpr auto 
    min(
        sequence<indexes_c...>)
    {
        return 
        thodd::min(
            size_t{indexes_c}...);
    }



    template<
        size_t min_c, 
        size_t max_c>
    constexpr auto 
    make_sequence(
        lowerbound<min_c>, 
        upperbound<max_c>,
        auto __step)
    {
        static_assert(
            min_c <= max_c,
            "(min_c <= max_c) not" 
            "respected for make_seqence");

        return 
        sequence_detail::
        make_sequence(
            lowerbound<min_c>{}, 
            upperbound<max_c>{},
            sequence<min_c>{}, 
            __step);
    }


    template<
        size_t min_c, 
        size_t max_c>
    constexpr auto 
    make_sequence(
        lowerbound<min_c>, 
        upperbound<max_c>)
    {
        return 
        sequence_detail::
        make_sequence(
            lowerbound<min_c>{}, 
            upperbound<max_c>{},
            sequence<min_c>{}, 
            [] (auto __item) { return __item + 1; });
    }


    template<
        size_t max_c>
    constexpr auto 
    make_sequence(
        upperbound<max_c>,
        auto __step)
    {
        return 
        make_sequence(
            lowerbound<0>{}, 
            upperbound<max_c>{}, 
            __step);
    }


    template<
        size_t max_c>
    constexpr auto 
    make_sequence(
        upperbound<max_c>)
    {
        return 
        make_sequence(
            lowerbound<0>{}, 
            upperbound<max_c>{}, 
            [] (auto __item) { return __item + 1; });
    }


    template<
        size_t ... indexes_c, 
        size_t ... items_c>
    constexpr sequence<sequence_detail::at_c(sizeof(indexes_c) - 1 - indexes_c, size_t{items_c}...)...>
    reverse_sequence(
        sequence<items_c...>, 
        sequence<indexes_c...>)
    {
        return {};
    }

    


    template<
        size_t ... indexes_c>
    constexpr auto 
    reverse_sequence(
        sequence<indexes_c...>)
    {
        return 
        reverse_sequence(
            sequence<indexes_c...>{}, 
            sequence_detail::simple_reverse_sequence(
                make_sequence(
                    upperbound<sizeof...(indexes_c) - 1>{})));
    }
}

#endif  