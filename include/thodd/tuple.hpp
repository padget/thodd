#ifndef __THODD_TUPLE_HPP__
#  define __THODD_TUPLE_HPP__

#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>

namespace thodd
{
    namespace detail
    {

        template<
            typename item_t,
            size_t _index>
        struct tuple_element_pod
        {
            item_t item;

            constexpr tuple_element_pod() = default;

            template<
                typename oitem_t>
            explicit constexpr
            tuple_element_pod(
                oitem_t&& _oitem):
                item{perfect<oitem_t>(_oitem)} {}
        };


        template<
            size_t _index,
            typename item_t>
        constexpr item_t&
        tuple_get(
            tuple_element_pod<item_t, _index>& _pod)
        {
            return _pod.item;
        }

        template<
            size_t _index,
            typename item_t>
        constexpr item_t const&
        tuple_get(
            tuple_element_pod<item_t, _index> const& _pod)
        {
            return _pod.item;
        }

        template<
            size_t _index,
            typename item_t>
        constexpr item_t&&
        tuple_get(
            tuple_element_pod<item_t, _index>&& _pod)
        {
            return rvalue(_pod.item);
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
            static_assert(sizeof...(items_t) > 0, "");
            constexpr tuple_indexed() = default;

            template<
                typename ... oitem_t>
            explicit constexpr
            tuple_indexed(
                oitem_t&& ... _items) :
                tuple_element_pod<items_t, indexes_c>{perfect<oitem_t>(_items)}... {}

            explicit constexpr
            tuple_indexed(
                tuple_indexed<items_t...>&& _other) :
                tuple_element_pod<items_t, indexes_c>{rvalue(tuple_get<indexes_c>(_other))}... {}

            explicit constexpr
            tuple_indexed(
                tuple_indexed<items_t...> const& _other) :
                tuple_element_pod<items_t, indexes_c>{tuple_get<indexes_c>(_other)}... {}
        };


        /// Operator+ that concat
        /// two tuples
        template<
            std::size_t ... indexes1_c,
            typename    ... items1_t,
            std::size_t ... indexes2_c,
            typename    ... items2_t>
        constexpr auto
        operator+(
            tuple_indexed<indexes<indexes1_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes2_c...>, items2_t...> const& _tuple2)
        {
            return tuple_indexed<
                    make_indexes<sizeof...(indexes1_c) 
                               + sizeof...(indexes2_c)>, 
                    items1_t..., items2_t...>
                  {tuple_get<indexes1_c>(_tuple1)..., 
                   tuple_get<indexes2_c>(_tuple2)...};
        }

        /// Operator== that compare
        /// two tuples
        template<
            size_t   ... indexes_c,
            typename ... items1_t,
            typename ... items2_t>
        constexpr bool
        operator==(
            tuple_indexed<indexes<indexes_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes_c...>, items2_t...> const& _tuple2)
        {
            if(&_tuple1 == &_tuple2)
                return true;

            bool __res{true};
            repeat{(__res &=  tuple_get<indexes_c>(_tuple1) == tuple_get<indexes_c>(_tuple2), 0)...};
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
        operator!=(
            tuple_indexed<indexes<indexes1_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes2_c...>, items2_t...> const& _tuple2)
        {
            return !(_tuple1 == _tuple2);
        }

        /// Operator< that compare
        /// two tuples
        template<
            size_t ... indexes_c,
            typename ... items1_t,
            typename ... items2_t>
        constexpr bool
        operator<(
            tuple_indexed<indexes<indexes_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes_c...>, items2_t...> const& _tuple2)
        {
            if(&_tuple1 == &_tuple2)
                return false;

            bool _res_{true};
            repeat{(_res_ &= tuple_get<indexes_c>(_tuple1) < tuple_get<indexes_c>(_tuple2), 0)...};
            return _res_;
        }

        /// Operator<= that compare
        template<
            std::size_t ... indexes_c,
            typename ... items1_t,
            typename ... items2_t>
        constexpr bool
        operator<=(
            tuple_indexed<indexes<indexes_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes_c...>, items2_t...> const& _tuple2)
        {
            return !(_tuple2 < _tuple1);
        }


        template<
            std::size_t ... indexes_c,
            typename ... items1_t,
            typename ... items2_t>
        constexpr bool
        operator>(
            tuple_indexed<indexes<indexes_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes_c...>, items2_t...> const& _tuple2)
        {
            return _tuple2 < _tuple1;
        }


        /// Operator>= that compare
        /// two tuples
        template<
            std::size_t ... indexes_c,
            typename ... items1_t,
            typename ... items2_t>
        constexpr bool
        operator>=(
            tuple_indexed<indexes<indexes_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes_c...>, items2_t...> const& _tuple2)
        {
            return !(_tuple1 < _tuple2);
        }
    }



    template<
        typename ... items_t>
    struct tuple_indexed:
        public detail::tuple_indexed<make_indexes<sizeof...(items_t)>, items_t...>
    {
        using base_t = detail::tuple_indexed<make_indexes<sizeof...(items_t)>, items_t...>;

        constexpr tuple_indexed() = default;

        template<
            typename ... oitem_t>
        explicit constexpr
        tuple_indexed(
            oitem_t&&... _items):
            base_t{perfect<oitem_t>(_items)...} {}


        template<
            typename other_t,
            typename = meta::enable_if<meta::is_same<meta::remove_all<other_t>, tuple_indexed>::value>>
        constexpr
        tuple_indexed(
            other_t&& _other):
            base_t{perfect<other_t>(_other)} {}


        template<
            size_t _index>
        constexpr decltype(auto)
        get()
        {
            return detail::tuple_get<_index>(*this);
        }


        template<
            size_t _index>
        constexpr decltype(auto)
        get() const
        {
            return detail::tuple_get<_index>(*this);
        }
    };

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
            repeat{(_left.template get<indexes_c>() = perfect<right_t>(_right).template get<indexes_c>(), int{})... };
        }


        template<
            typename tuple_t,
            typename func_t,
            size_t ... indexes_c>
        constexpr auto
        apply(
            tuple_t&& _tuple,
            func_t&& _func,
            indexes<indexes_c...>)
        -> decltype(perfect<func_t>(_func)(perfect<tuple_t>(_tuple).template get<indexes_c>()...))
        {
            return perfect<func_t>(_func)(perfect<tuple_t>(_tuple).template get<indexes_c>()...);
        }

        template<
			typename tuple_t,
			typename func_t,
			size_t ... indexes_c,
			typename ... args_t>
		constexpr auto
		functional_apply(
			tuple_t&& _tuple,
			func_t&& _func,
			args_t&& ... _args,
			indexes<indexes_c...>)
		-> decltype(perfect<func_t>(_func)(perfect<tuple_t>(_tuple).template get<indexes_c>()(perfect<args_t>(_args)...)...))
		{
			return perfect<func_t>(_func)(perfect<tuple_t>(_tuple).template get<indexes_c>()(perfect<args_t>(_args)...)...);
		}


        template<
            typename tuple_t,
            typename func_t,
            size_t ... indexes_c>
        constexpr void
        foreach(
            tuple_t&& _tuple,
            func_t&& _func,
            indexes<indexes_c...>)
        {
            repeat{(perfect<func_t>(_func)(perfect<tuple_t>(_tuple).template get<indexes_c>()), 0)...};
        }
    }


   


    template<
        typename ... items_t>
    struct tuple
    {
        tuple_indexed<items_t...> indexed;

    private:
        template<
            typename other_t,
            size_t ... indexes_c>
        explicit constexpr
        tuple(
            other_t&& _other,
            indexes<indexes_c...>) :
            indexed{perfect<other_t>(_other).template get<indexes_c>()...} {}

    public:
        constexpr tuple() = default;

        explicit constexpr tuple(
		    items_t const&... _items): 
            indexed{_items...} {}

        template<
            typename ... oitems_t>
        explicit constexpr tuple(
		    oitems_t&&... _oitems): 
            indexed{perfect<oitems_t>(_oitems)...} {}

    public:
        template<
            typename ... oitems_t>
        constexpr tuple(
            tuple<oitems_t...> const& _other) :
            tuple{_other, make_indexes<sizeof...(items_t)>{}}{}

        template<
            typename ... oitems_t>
        constexpr tuple(
            tuple<oitems_t...>&& _other) :
            tuple{_other, make_indexes<sizeof...(items_t)>{}}{}

    public:
        template<
            typename ... oitems_t>
        constexpr tuple&
        operator=(
            tuple<oitems_t...> const& _other)
        {
            tuple_algorithm::assign(this->indexed, _other.indexed, make_indexes<sizeof...(items_t)>{});
        }

        template<
            typename ... oitems_t>
        constexpr tuple&
        operator=(
            tuple<oitems_t...>&& _other)
        {
            tuple_algorithm::assign(this->indexed, _other.indexed, make_indexes<sizeof...(items_t)>{});
        }

        template<
            size_t _index>
        constexpr auto
        get()
        -> decltype(indexed.template get<_index>())
        {
            return indexed.template get<_index>();
        }

        template<
            size_t _index>
        constexpr auto
        get() const
        -> decltype(indexed.template get<_index>())
        {
            return indexed.template get<_index>();
        }

        template<
            typename func_t>
        constexpr auto
        apply(
            func_t&& _func)
        -> decltype(tuple_algorithm::apply(this->indexed, perfect<func_t>(_func), make_indexes<sizeof...(items_t)>{}))
        {
            return tuple_algorithm::apply(this->indexed,
                                          perfect<func_t>(_func),
                                          make_indexes<sizeof...(items_t)>{});
        }

        template<
            typename func_t>
        constexpr auto
        apply(
            func_t&& _func) const
        -> decltype(tuple_algorithm::apply(this->indexed, perfect<func_t>(_func), make_indexes<sizeof...(items_t)>{}))
        {
            return tuple_algorithm::apply(this->indexed,
                                          perfect<func_t>(_func),
                                          make_indexes<sizeof...(items_t)>{});
        }

        template<
			typename func_t,
			typename ... args_t>
		constexpr auto
		functional_apply(
			func_t&& _func,
			args_t&&... _args)
		-> decltype(tuple_algorithm::functional_apply(this->indexed, perfect<func_t>(_func), make_indexes<sizeof...(items_t)>{}))
		{
			return tuple_algorithm::functional_apply(this->indexed,
										  perfect<func_t>(_func),
										  perfect<args_t>(_args)...,
										  make_indexes<sizeof...(items_t)>{});
		}

        template<
			typename func_t,
			typename ... args_t>
		constexpr auto
		functional_apply(
			func_t&& _func,
			args_t&&... _args) const
		-> decltype(tuple_algorithm::functional_apply(this->indexed, perfect<func_t>(_func), make_indexes<sizeof...(items_t)>{}))
		{
			return tuple_algorithm::functional_apply(this->indexed,
										  perfect<func_t>(_func),
										  perfect<args_t>(_args)...,
										  make_indexes<sizeof...(items_t)>{});
		}

        template<
            typename func_t>
        constexpr void
        foreach(
            func_t&& _func)
        {
            tuple_algorithm::foreach(this->indexed,
                                     perfect<func_t>(_func),
                                     make_indexes<sizeof...(items_t)>{});
        }

        template<
            typename func_t>
        constexpr void
        foreach(
            func_t&& _func) const
        {
            tuple_algorithm::foreach(this->indexed,
                                     perfect<func_t>(_func),
                                     make_indexes<sizeof...(items_t)>{});
        }
    };



    template<>
    struct tuple<>
    {
    public:
        constexpr tuple() = default;
    };


    /// Tuple factory
    template<
        typename... items_t>
    constexpr tuple<items_t...>
    make_tuple(
        items_t&&... _items)
    {
        return tuple<items_t...>{perfect<items_t>(_items)...};
    }


    /// Tuple factory
    /// for reference
    /// only
    template<
        typename... items_t>
    inline tuple<items_t&...>
    tie(
        items_t&... _items)
    {
        return {_items...};
    }


    /// Tuple factory
    /// that return
    /// a perfecting
    /// tuple (uref)
    template<
        typename ... items_t>
    inline auto
    perfect_as_tuple(
        items_t&&... _items)
    {
        return tuple<items_t&&...>(perfect<items_t>(_items)...);
    }


    template<
        size_t index_c,
        typename ... items_t>
    inline auto
    get(
        tuple<items_t...>&& __tuple)
    -> decltype(auto)
    {
        return __tuple.template get<index_c>();
    }


    template<
        size_t index_c,
        typename ... items_t>
    inline auto
    get(
        tuple<items_t...> const& __tuple)
    -> decltype(auto)
    {
        return __tuple.template get<index_c>();
    }
    

    template<
        size_t index_c,
        typename ... items_t>
    inline auto
    get(
        tuple<items_t...>& __tuple)
    -> decltype(auto)
    {
        return __tuple.template get<index_c>();
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


    /// Operator+ that concat
    /// two tuples
    template<
        typename ... items1_t,
        typename item2_t>
    constexpr auto
    operator + (
        tuple<items1_t...> const& __tuple1,
        item2_t&& __item2)
    {
        using tpl = tuple<items1_t..., item2_t>;

        return tpl{__tuple1.indexed + make_tuple(perfect<item2_t>(__item2)).indexed};
    }


    /// Operator+ that concat
    /// two tuples
    template<
        typename item1_t,
        typename ... items2_t>
    constexpr auto
    operator + (
        item1_t&& __item1,
        tuple<items2_t...> const& __tuple2)
    {
        using tpl = tuple<item1_t, items2_t...>;

        return tpl{make_tuple(perfect<item1_t>(__item1)).indexed + __tuple2.indexed};
    }


    /// Operator+ that concat
    /// two tuples
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr auto
    operator+(
        tuple<items1_t...> const& _tuple1,
        tuple<items2_t...> const& _tuple2)
    {
        using tpl = tuple<items1_t..., items2_t...>;

        return  tpl{_tuple1.indexed + _tuple2.indexed};
    }


    /// Operator== that compare
    /// two tuples
    template<
        std::size_t ... indexes_c,
        typename    ... items1_t,
        typename    ... items2_t>
    constexpr bool
    operator==(
        tuple<items1_t...> const& _tuple1,
        tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.indexed == _tuple2.indexed;
    }


    /// Operator!= that compare
    /// two tuples
    template<
        std::size_t ... indexes_c,
        typename    ... items1_t,
        typename    ... items2_t>
    constexpr bool
    operator!=(
        tuple<items1_t...> const& _tuple1,
        tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.indexed != _tuple2.indexed;
    }


    /// Operator< that compare
    /// two tuples
    template<
        std::size_t ... indexes_c,
        typename    ... items1_t,
        typename    ... items2_t>
    constexpr bool
    operator<(
        tuple<items1_t...> const& _tuple1,
        tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.indexed < _tuple2.indexed;
    }


    /// Operator<= that compare
    template<
        std::size_t ... indexes_c,
        typename    ... items1_t,
        typename    ... items2_t>
    constexpr bool
    operator<=(
        tuple<items1_t...> const& _tuple1,
        tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.indexed <= _tuple2.indexed;
    }


    template<
        std::size_t ... indexes_c,
        typename    ... items1_t,
        typename    ... items2_t>
    constexpr bool
    operator>(
        tuple<items1_t...> const& _tuple1,
        tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.indexed > _tuple2.indexed;
    }


    /// Operator>= that compare
    /// two tuples
    template<
        std::size_t ... indexes_c,
        typename    ... items1_t,
        typename    ... items2_t>
    constexpr bool
    operator>=(
        tuple<items1_t...> const& _tuple1,
        tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.indexed >= _tuple2.indexed;
    }
}

#endif
