#ifndef __THODD_TUPLE_HPP__
#  define __THODD_TUPLE_HPP__

#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>

#  include <thodd/tuple_indexed.hpp>

namespace thodd
{
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
    struct tuple
    {
        using base_t = tuple_indexed<thodd::make_indexes<sizeof...(items_t)>, items_t...>;
        base_t storage;

    private:
        constexpr base_t&
        pstorage() & 
        {
            return storage;
        }

        constexpr base_t const&
        pstorage() const&
        {
            return storage;
        }

        constexpr base_t&&
        pstorage() &&
        {
            return thodd::rvalue(storage);
        }


    private:    
        template<
            typename ... oitems_t,
            size_t ... indexes_c>
        explicit constexpr
        tuple(
            tuple<oitems_t...> const& __other,
            indexes<indexes_c...>) :
            storage{ thodd::get<indexes_c>(__other.storage)... } {}

        template<
            typename ... oitems_t,
            size_t ... indexes_c>
        explicit constexpr
        tuple(
            tuple<oitems_t...>&& __other,
            indexes<indexes_c...>) :
            storage{ thodd::rvalue(thodd::get<indexes_c>(__other.storage))... } {}

    public:
        constexpr tuple() = default;


        template<
            typename ... oitems_t>
        explicit constexpr tuple(
            oitems_t const&... __oitems) :
            storage{ __oitems... } {}


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
            tuple_algorithm::assign(this->storage, __other.storage, make_indexes<sizeof...(items_t)>{});
            return *this;
        }


        template<
            typename ... oitems_t>
        inline tuple&
        operator = (
            tuple<oitems_t...>&& __other)
        {
            tuple_algorithm::assign(this->storage, __other.storage, make_indexes<sizeof...(items_t)>{});
            return *this;
        }


        template<
            typename ... oitems_t>
        inline tuple&
        operator = (
            tuple<oitems_t...>& __other)
        {
            tuple_algorithm::assign(this->storage, __other.storage, make_indexes<sizeof...(items_t)>{});
            return *this;
        }

    public:
        template<
            size_t index_c>
        constexpr auto
        get() const 
        -> decltype(auto)
        {
            return thodd::get<index_c>(this->storage);
        }


        template<
            size_t index_c>
        constexpr auto
        get()  
        -> decltype(auto)
        {
            return thodd::get<index_c>(this->storage);
        }

    public:
        constexpr auto
        apply(
            auto&& __func)
        -> decltype(auto)
        {
            return
            thodd::apply(
                this->pstorage(),
                perfect<decltype(__func)>(__func));
        }

        constexpr auto
        apply(
            auto&& __func) const
        -> decltype(auto)
        {
            return
            thodd::apply(
                this->pstorage(),
                perfect<decltype(__func)>(__func));
        }

        constexpr auto
        functional_apply(
            auto&& __func,
            auto&& ... __args)
        -> decltype(auto)
        {
            return 
            thodd::functional_apply(
                this->pstorage(),
                perfect<decltype(__func)>(__func),
                perfect<decltype(__args)>(__args)...);
        }

        constexpr auto
        functional_apply(
            auto&& __func,
            auto&& ... __args) const
        -> decltype(auto)
        {
            return 
            thodd::functional_apply(
                this->pstorage(),
                perfect<decltype(__func)>(__func),
                perfect<decltype(__args)>(__args)...);
        }


        constexpr auto
        foreach(
            auto&& __func)
        -> decltype(auto)
        {
            return 
            thodd::foreach(
                this->pstorage(),
                perfect<decltype(__func)>(__func));
        }

        constexpr auto
        foreach(
            auto&& __func) const
        -> decltype(auto)
        {
            return 
            thodd::foreach(
                this->pstorage(),
                perfect<decltype(__func)>(__func));
        }


        constexpr auto
        foreach_join(
            auto&& __func,
            auto&& __other)
        -> decltype(auto)
        {
            return 
            thodd::foreach_join(
                this->pstorage(),
                perfect<decltype(__func)>(__func), 
                perfect<decltype(__other)>(__other));
        }

        constexpr auto
        foreach_join(
            auto&& __func,
            auto&& __other) const
        -> decltype(auto)
        {
            return 
            thodd::foreach_join(
                this->pstorage(),
                perfect<decltype(__func)>(__func), 
                perfect<decltype(__other)>(__other));
        }
    };



    // template<>
    // struct tuple<>
    // {
    // public:
    //     constexpr tuple() = default;
    // };


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


     /// Operator== that compare
    /// two tuples
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator == (
        tuple<items1_t...> const& __tuple1,
        tuple<items2_t...> const& __tuple2)
    {
        return 
        __tuple1.storage 
        == __tuple2.storage;
    }


    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator != (
        tuple<items1_t...> const& __tuple1,
        tuple<items2_t...> const& __tuple2)
    {
        return 
        __tuple1.storage 
        != __tuple2.storage ;
    }

    /// Operator< that compare
    /// two tuples
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator < (
        tuple<items1_t...> const& __tuple1,
        tuple<items2_t...> const& __tuple2)
    {
        return 
        __tuple1.storage
        < __tuple2.storage;
    }


    /// Operator<= that compare
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator <= (
        tuple<items1_t...> const& __tuple1,
        tuple<items2_t...> const& __tuple2)
    {  
        return 
        __tuple1.storage
        <= __tuple2.storage;
    }


    /// Operator<= that compare
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator > (
        tuple<items1_t...> const& __tuple1,
        tuple<items2_t...> const& __tuple2)
    {  
        return 
        __tuple1.storage
        > __tuple2.storage;
    }


    /// Operator<= that compare
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator >= (
        tuple<items1_t...> const& __tuple1,
        tuple<items2_t...> const& __tuple2)
    {
        return 
        __tuple1.storage
        >= __tuple2.storage;
    }


     template<
        typename ... litems_t, 
        typename ... ritems_t>
    constexpr auto
    operator + (
        tuple<litems_t...> const& __ltuple, 
        tuple<ritems_t...> const& __rtuple)
    {
        return 
        tuple<litems_t..., ritems_t...>
        { __ltuple.storage + __rtuple.storage };
    }


    template<
        typename ... litems_t, 
        typename ... ritems_t>
    constexpr auto
    operator + (
        tuple<litems_t...> const& __ltuple, 
        tuple<ritems_t...>&& __rtuple)
    {
        return 
        tuple<litems_t..., ritems_t...>
        { __ltuple.storage + thodd::rvalue(__rtuple.storage) };
    }


    template<
        typename ... litems_t, 
        typename ... ritems_t>
    constexpr auto
    operator + (
        tuple<litems_t...>&& __ltuple, 
        tuple<ritems_t...> const& __rtuple)
    {
        return 
        tuple<litems_t..., ritems_t...>
        { thodd::rvalue(__ltuple.storage) + __rtuple.storage };
    }


    template<
        typename ... litems_t, 
        typename ... ritems_t>
    constexpr auto
    operator + (
        tuple<litems_t...>&& __ltuple, 
        tuple<ritems_t...>&& __rtuple)
    {
        return 
        tuple<litems_t..., ritems_t...>
        { thodd::rvalue(__ltuple.storage) + thodd::rvalue(__rtuple.storage) };
    }
}

#endif