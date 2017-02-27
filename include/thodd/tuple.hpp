#ifndef __THODD_TUPLE_HPP__
#  define __THODD_TUPLE_HPP__

#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>

namespace thodd
{
    template<
        typename item_t,
        size_t index_c>
    struct tuple_element_pod
    {
        item_t item;

        constexpr tuple_element_pod() = default;

        explicit constexpr
        tuple_element_pod(
            auto&& __oitem):
            item{ perfect<decltype(__oitem)>(__oitem) } {}
    };


    template<
        size_t index_c,
        typename item_t>
    constexpr item_t&
    get(
        tuple_element_pod<item_t, index_c>& _pod)
    {
        return 
        _pod.item;
    }


    template<
        size_t index_c,
        typename item_t>
    constexpr item_t const&
    get(
        tuple_element_pod<item_t, index_c> const& _pod)
    {
        return 
        _pod.item;
    }


    template<
        size_t index_c,
        typename item_t>
    constexpr item_t&&
    get(
        tuple_element_pod<item_t, index_c>&& _pod)
    {
        return 
        thodd::rvalue(_pod.item);
    }


    template<
        typename indexes_t,
        typename ... items_t>
    struct tuple_indexed;


    template<
        size_t... indexes_c,
        typename ... items_t>
    struct tuple_indexed<indexes<indexes_c...>, items_t...>:
        public tuple_element_pod<items_t, indexes_c>...
    {
    public:
        constexpr tuple_indexed() = default;

        template<
            typename ... oitems_t>
        explicit constexpr
        tuple_indexed(
            oitems_t&&... __items) :
            tuple_element_pod<items_t, indexes_c>{ perfect<oitems_t>(__items) }... {}

    public:
        template<
            typename ... oitems_t>
        explicit constexpr
        tuple_indexed(
            tuple_indexed<oitems_t...>&& __other) :
            tuple_element_pod<items_t, indexes_c>{ thodd::rvalue(thodd::get<indexes_c>(__other)) }... {}

        template<
            typename ... oitems_t>
        explicit constexpr
        tuple_indexed(
            tuple_indexed<oitems_t...> const& __other) :
            tuple_element_pod<items_t, indexes_c>{ thodd::get<indexes_c>(__other) }... {}

        template<
            typename ... oitems_t>
        explicit constexpr
        tuple_indexed(
            tuple_indexed<oitems_t...>& __other) :
            tuple_indexed<items_t...>{ const_cast<tuple_indexed<items_t...> const&>(__other) } {}
    };


    /// Operator== that compare
    /// two tuples
    template<
        size_t   ... indexes_c,
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator==(
        tuple_indexed<indexes<indexes_c...>, items1_t...> const& __tuple1,
        tuple_indexed<indexes<indexes_c...>, items2_t...> const& __tuple2)
    {
        if(&__tuple1 == &__tuple2)
            return true;

        bool __res{true};
        repeat{(__res &= thodd::get<indexes_c>(__tuple1) == thodd::get<indexes_c>(__tuple2), 0)...};
        return __res;
    }

    /// Specialization that return false
    /// because the sizes are different !
    template<
        size_t   ... indexes1_c,
        typename ... items1_t,
        size_t   ... indexes2_c,
        typename ... items2_t>
    constexpr bool
    operator==(
        tuple_indexed<indexes<indexes1_c...>, items1_t...> const&,
        tuple_indexed<indexes<indexes2_c...>, items2_t...> const&)
    {
        return false;
    }

    /// Operator!= that compare
    /// two tuples
    template<
        size_t ... indexes1_c,
        typename ... items1_t,
        size_t ... indexes2_c,
        typename ... items2_t>
    constexpr bool
    operator != (
        tuple_indexed<indexes<indexes1_c...>, items1_t...> const& __tuple1,
        tuple_indexed<indexes<indexes2_c...>, items2_t...> const& __tuple2)
    {
        return !(__tuple1 == __tuple2);
    }

    /// Operator< that compare
    /// two tuples
    template<
        size_t ... indexes_c,
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator < (
        tuple_indexed<indexes<indexes_c...>, items1_t...> const& __tuple1,
        tuple_indexed<indexes<indexes_c...>, items2_t...> const& __tuple2)
    {
        if(&__tuple1 == &__tuple2)
            return false;

        bool _res_{true};
        repeat{(_res_ &= thodd::get<indexes_c>(__tuple1) < thodd::get<indexes_c>(__tuple2), 0)...};
        return _res_;
    }

    /// Operator< that compare
    /// two tuples
    template<
        size_t ... indexes_c,
        typename ... items1_t,
        size_t ... indexes2_c,
        typename ... items2_t>
    constexpr bool
    operator < (
        tuple_indexed<indexes<indexes_c...>, items1_t...> const& __tuple1,
        tuple_indexed<indexes<indexes2_c...>, items2_t...> const& __tuple2)
    {
        return false;
    }

    /// Operator<= that compare
    template<
        size_t ... indexes_c,
        typename ... items1_t,
        size_t ... indexes2_c,
        typename ... items2_t>
    constexpr bool
    operator <= (
        tuple_indexed<indexes<indexes_c...>, items1_t...> const& __tuple1,
        tuple_indexed<indexes<indexes2_c...>, items2_t...> const& __tuple2)
    {
        return !(__tuple2 < __tuple1);
    }


    template<
        size_t ... indexes_c,
        typename ... items1_t,
        size_t ... indexes2_c,
        typename ... items2_t>
    constexpr bool
    operator > (
        tuple_indexed<indexes<indexes_c...>, items1_t...> const& __tuple1,
        tuple_indexed<indexes<indexes2_c...>, items2_t...> const& __tuple2)
    {
        return !(__tuple2 <= __tuple1);
    }


    /// Operator>= that compare
    /// two tuples
    template<
        size_t ... indexes_c,
        typename ... items1_t,
        size_t ... indexes2_c,
        typename ... items2_t>
    constexpr bool
    operator >= (
        tuple_indexed<indexes<indexes_c...>, items1_t...> const& __tuple1,
        tuple_indexed<indexes<indexes2_c...>, items2_t...> const& __tuple2)
    {
        return !(__tuple1 < __tuple2);
    }


    template<
        typename func_t,
        typename ... items_t,
        size_t ... indexes_c>
    constexpr auto
    apply(
        tuple_indexed<indexes<indexes_c...>, items_t...>& __tuple,
        func_t&& __func)
    -> decltype(auto)
    {
        return perfect<func_t>(__func)(thodd::get<indexes_c>(__tuple)...);
    }


    template<
        typename func_t,
        typename ... items_t,
        size_t ... indexes_c>
    constexpr auto
    apply(
        tuple_indexed<indexes<indexes_c...>, items_t...> const& __tuple,
        func_t&& __func)
    -> decltype(auto)
    {
        return perfect<func_t>(__func)(thodd::get<indexes_c>(__tuple)...);
    }


    template<
        typename func_t,
        typename ... items_t,
        size_t ... indexes_c>
    constexpr auto
    apply(
        tuple_indexed<indexes<indexes_c...>, items_t...>&& __tuple,
        func_t&& __func)
    -> decltype(auto)
    {
        return perfect<func_t>(__func)(thodd::get<indexes_c>(__tuple)...);
    }


    template<
        typename ... items_t,
        typename func_t,
        size_t ... indexes_c>
    constexpr void
    foreach(
        tuple_indexed<indexes<indexes_c...>, items_t...>& __tuple,
        func_t&& __func)
    {
        repeat{(perfect<func_t>(__func)(thodd::get<indexes_c>(__tuple)), 0)...};
    }


    template<
        typename ... items_t,
        typename func_t,
        size_t ... indexes_c>
    constexpr void
    foreach(
        tuple_indexed<indexes<indexes_c...>, items_t...> const& __tuple,
        func_t&& __func)
    {
        repeat{(perfect<func_t>(__func)(thodd::get<indexes_c>(__tuple)), 0)...};
    }


    template<
        typename ... items_t,
        typename func_t,
        size_t ... indexes_c>
    constexpr void
    foreach(
        tuple_indexed<indexes<indexes_c...>, items_t...>&& __tuple,
        func_t&& __func)
    {
        repeat{(perfect<func_t>(__func)(thodd::get<indexes_c>(__tuple)), 0)...};
    }


    template<
        typename ... items_t,
        typename func_t,
        size_t ... indexes_c,
        typename ... args_t>
    constexpr auto
    functional_apply(
        tuple_indexed<indexes<indexes_c...>, items_t...>& __tuple,
        func_t&& __func,
        args_t&&... _args)
    -> decltype(auto)
    {
        return perfect<func_t>(__func)(thodd::get<indexes_c>(__tuple)(perfect<args_t>(_args)...)...);
    }


    template<
        typename ... items_t,
        typename func_t,
        size_t ... indexes_c,
        typename ... args_t>
    constexpr auto
    functional_apply(
        tuple_indexed<indexes<indexes_c...>, items_t...> const& __tuple,
        func_t&& __func,
        args_t&&... _args)
    -> decltype(auto)
    {
        return perfect<func_t>(__func)(thodd::get<indexes_c>(__tuple)(perfect<args_t>(_args)...)...);
    }


    template<
        typename ... items_t,
        typename func_t,
        size_t ... indexes_c,
        typename ... args_t>
    constexpr auto
    functional_apply(
        tuple_indexed<indexes<indexes_c...>, items_t...>&& __tuple,
        func_t&& __func,
        args_t&&... _args)
    -> decltype(auto)
    {
        return perfect<func_t>(__func)(thodd::get<indexes_c>(__tuple)(perfect<args_t>(_args)...)...);
    }


    template<
        typename ... items_t,
        typename tuple1_t,
        typename func_t,
        size_t ... indexes_c>
    constexpr void
    foreach_join(
        tuple_indexed<indexes<indexes_c...>, items_t...>& __tuple,
        func_t&& __func,
        tuple1_t&& __tuple1)
    {
        repeat{(perfect<func_t>(__func)(
                    thodd::get<indexes_c>(__tuple),
                    thodd::get<indexes_c>(perfect<tuple1_t>(__tuple1))), 0)...};
    }

     
    template<
        typename ... items_t,
        typename tuple1_t,
        typename func_t,
        size_t ... indexes_c>
    constexpr void
    foreach_join(
        tuple_indexed<indexes<indexes_c...>, items_t...> const& __tuple,
        func_t&& __func,
        tuple1_t&& __tuple1)
    {
        repeat{(perfect<func_t>(__func)(
                    thodd::get<indexes_c>(__tuple),
                    thodd::get<indexes_c>(perfect<tuple1_t>(__tuple1))), 0)...};
    }

    
    template<
        typename ... items_t,
        typename tuple1_t,
        typename func_t,
        size_t ... indexes_c>
    constexpr void
    foreach_join(
        tuple_indexed<indexes<indexes_c...>, items_t...>&& __tuple,
        func_t&& __func,
        tuple1_t&& __tuple1)
    {
        repeat{(perfect<func_t>(__func)(
                    thodd::get<indexes_c>(__tuple),
                    thodd::get<indexes_c>(perfect<tuple1_t>(__tuple1))), 0)...};
    }


    namespace tuple_algorithm
    {
        template<
            typename left_t,
            typename right_t,
            size_t ... indexes_c>
        constexpr void
        assign(
            left_t& _left,
            right_t&& _right,
            indexes<indexes_c...>)
        {
            repeat{(thodd::get<indexes_c>(_left) = thodd::get<indexes_c>(perfect<right_t>(_right)), 0)... };
        }
    }


    template<
        typename ... items_t>
    struct tuple:
       public tuple_indexed<thodd::make_indexes<sizeof...(items_t)>, items_t...>
    {
    private:
        using base_t = tuple_indexed<thodd::make_indexes<sizeof...(items_t)>, items_t...>;

        template<
            typename ... oitems_t,
            size_t ... indexes_c>
        explicit constexpr
        tuple(
            tuple<oitems_t...> const& __other,
            indexes<indexes_c...>) :
            base_t{ thodd::get<indexes_c>(__other)... } {}

        template<
            typename ... oitems_t,
            size_t ... indexes_c>
        explicit constexpr
        tuple(
            tuple<oitems_t...>&& __other,
            indexes<indexes_c...>) :
            base_t{ thodd::rvalue(thodd::get<indexes_c>(__other))... } {}

    public:
        constexpr tuple() = default;

        explicit constexpr tuple(
            auto&&... __oitems) :
            base_t{ perfect<decltype(__oitems)>(__oitems)... } {}

    public:
        template<
            typename ... oitems_t>
        constexpr tuple(
            tuple<oitems_t...> const& __other) :
            tuple{ __other, make_indexes<sizeof...(items_t)>{} } {}

        template<
            typename ... oitems_t>
        constexpr tuple(
            tuple<oitems_t...>&& __other) :
            tuple{ __other, make_indexes<sizeof...(items_t)>{} } {}

        template<
            typename ... oitems_t>
        constexpr tuple(
            tuple<oitems_t...>& __other) :
            tuple{ const_cast<tuple<oitems_t...> const&>(__other) } {}

    public:
        template<
            typename ... oitems_t>
        inline tuple&
        operator = (
            tuple<oitems_t...> const& __other)
        {
            tuple_algorithm::assign(*this, __other, make_indexes<sizeof...(items_t)>{});
            return *this;
        }

        template<
            typename ... oitems_t>
        inline tuple&
        operator = (
            tuple<oitems_t...>&& __other)
        {
            tuple_algorithm::assign(*this, __other, make_indexes<sizeof...(items_t)>{});
            return *this;
        }

        template<
            typename ... oitems_t>
        inline tuple&
        operator = (
            tuple<oitems_t...>& __other)
        {
            tuple_algorithm::assign(*this, __other, make_indexes<sizeof...(items_t)>{});
            return *this;
        }
    };



    template<>
    struct tuple<>
    {
    public:
        constexpr tuple() = default;
    };


    template<
        typename type_t>
    constexpr auto
    is_tuple(
        type_<type_t> const&)
    {
        return false;
    }


    template<
        typename ... items_t>
    constexpr auto
    is_tuple(
        type_<tuple<items_t...>> const&)
    {
        return true;
    }


    /// Tuple factory
    template<
        typename... items_t>
    constexpr tuple<items_t...>
    make_tuple(
        items_t&&... __items)
    {
        return
        tuple<items_t...>{
            perfect<items_t>(__items)...};
    }


    /// Tuple factory
    /// for reference
    /// only
    template<
        typename... items_t>
    constexpr tuple<items_t&...>
    tie(
        items_t&... __items)
    {
        return {__items...};
    }


    /// Tuple factory
    /// that return
    /// a perfecting
    /// tuple (uref)
    template<
        typename ... items_t>
    constexpr auto
    perfect_as_tuple(
        items_t&&... __items)
    {
        return
        tuple<items_t&&...>(
            perfect<items_t>(__items)...);
    }
 


    namespace detail
    {
        struct tuple_size_impl
        {
            template<
                typename ... items_t>
            constexpr size_t
            operator()(
                tuple<items_t...> const&) const
            {
                return sizeof...(items_t);
            }
        };
    }

    constexpr auto tuple_size = detail::tuple_size_impl{};


    template<
        typename ... litems_t, 
        size_t ... lindexes_c, 
        typename ... ritems_t, 
        size_t ... rindexes_c>
    constexpr auto
    operator + (
        tuple_indexed<indexes<lindexes_c...>, litems_t...> const& __ltuple, 
        tuple_indexed<indexes<rindexes_c...>, ritems_t...> const& __rtuple)
    {
        return 
        make_tuple(
            thodd::get<lindexes_c>(__ltuple)..., 
            thodd::get<rindexes_c>(__rtuple)...);
    }


    template<
        typename ... litems_t, 
        size_t ... lindexes_c, 
        typename ... ritems_t, 
        size_t ... rindexes_c>
    constexpr auto
    operator + (
        tuple_indexed<indexes<lindexes_c...>, litems_t...> const& __ltuple, 
        tuple_indexed<indexes<rindexes_c...>, ritems_t...>&& __rtuple)
    {
        return 
        make_tuple(
            thodd::get<lindexes_c>(__ltuple)..., 
            thodd::rvalue(thodd::get<rindexes_c>(__rtuple))...);
    }


    template<
        typename ... litems_t, 
        size_t ... lindexes_c, 
        typename ... ritems_t, 
        size_t ... rindexes_c>
    constexpr auto
    operator + (
        tuple_indexed<indexes<lindexes_c...>, litems_t...>&& __ltuple, 
        tuple_indexed<indexes<rindexes_c...>, ritems_t...> const& __rtuple)
    {
        return 
        make_tuple(
            thodd::rvalue(thodd::get<lindexes_c>(__ltuple))..., 
            thodd::get<rindexes_c>(__rtuple)...);
    }


    template<
        typename ... litems_t, 
        size_t ... lindexes_c, 
        typename ... ritems_t, 
        size_t ... rindexes_c>
    constexpr auto
    operator + (
        tuple_indexed<indexes<lindexes_c...>, litems_t...>&& __ltuple, 
        tuple_indexed<indexes<rindexes_c...>, ritems_t...>&& __rtuple)
    {
        return 
        make_tuple(
            thodd::rvalue(thodd::get<lindexes_c>(__ltuple))..., 
            thodd::rvalue(thodd::get<rindexes_c>(__rtuple))...);
    }
}

#endif