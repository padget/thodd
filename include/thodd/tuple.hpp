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

            explicit constexpr
            tuple_element_pod(
                auto&& __oitem):
                item{perfect<decltype(__oitem)>(__oitem)} {}
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
            constexpr tuple_indexed() = default;

            template<
                typename ... oitems_t>
            explicit constexpr
            tuple_indexed(
                oitems_t&&... _items) :
                tuple_element_pod<items_t, indexes_c>{ perfect<oitems_t>(_items) }... {}

            template<
                typename ... oitems_t>
            explicit constexpr
            tuple_indexed(
                tuple_indexed<oitems_t...>&& _other) :
                tuple_element_pod<items_t, indexes_c>{ thodd::rvalue(tuple_get<indexes_c>(_other)) }... {}

            template<
                typename ... oitems_t>
            explicit constexpr
            tuple_indexed(
                tuple_indexed<oitems_t...> const& _other) :
                tuple_element_pod<items_t, indexes_c>{ tuple_get<indexes_c>(_other) }... {}

            template<
                typename ... oitems_t>
            explicit constexpr 
            tuple_indexed(
                tuple_indexed<oitems_t...>& __other) :
                tuple_indexed<items_t...>{ const_cast<tuple_indexed<items_t...> const&>(__other) } {}
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

        /// Operator< that compare
        /// two tuples
        template<
            size_t ... indexes_c,
            typename ... items1_t,
            size_t ... indexes2_c,
            typename ... items2_t>
        constexpr bool
        operator<(
            tuple_indexed<indexes<indexes_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes2_c...>, items2_t...> const& _tuple2)
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
        operator<=(
            tuple_indexed<indexes<indexes_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes2_c...>, items2_t...> const& _tuple2)
        {
            return !(_tuple2 < _tuple1);
        }


        template<
            size_t ... indexes_c,
            typename ... items1_t,
            size_t ... indexes2_c,
            typename ... items2_t>
        constexpr bool
        operator>(
            tuple_indexed<indexes<indexes_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes2_c...>, items2_t...> const& _tuple2)
        {
            return !(_tuple2 <= _tuple1);
        }


        /// Operator>= that compare
        /// two tuples
        template<
            size_t ... indexes_c,
            typename ... items1_t,
            size_t ... indexes2_c,
            typename ... items2_t>
        constexpr bool
        operator>=(
            tuple_indexed<indexes<indexes_c...>, items1_t...> const& _tuple1,
            tuple_indexed<indexes<indexes2_c...>, items2_t...> const& _tuple2)
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
            typename ... oitems_t>
        explicit constexpr
        tuple_indexed(
            oitems_t&&... __oitems) :
            base_t{ perfect<oitems_t>(__oitems)... } {}

        template<
            typename ... oitems_t>
        explicit constexpr
        tuple_indexed(
            tuple_indexed<oitems_t...>&& __other) :
            base_t{ thodd::rvalue(__other) } {}

        template<
            typename ... oitems_t>
        explicit constexpr
        tuple_indexed(
            tuple_indexed<oitems_t...> const& __other) :
            base_t{ __other } {}

        template<
            typename ... oitems_t>
        explicit constexpr 
        tuple_indexed(
            tuple_indexed<oitems_t...>& __other) :
            base_t{ const_cast<tuple_indexed<oitems_t...> const&>(__other) } {}


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
        -> decltype(auto)
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
		-> decltype(auto)
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

        template<
            typename tuple_t,
            typename tuple1_t,
            typename func_t,
            size_t ... indexes_c>
        constexpr void
        foreach_join(
            indexes<indexes_c...>,

            tuple_t&& __tuple,
            func_t&& __func,
            tuple1_t&& __tuple1)
        {
            repeat{(perfect<func_t>(__func)(
                        perfect<tuple_t>(__tuple).template get<indexes_c>(), 
                        perfect<tuple1_t>(__tuple1).template get<indexes_c>()), 0)...};
        }
    }


   


    template<
        typename ... items_t>
    struct tuple
    {
        tuple_indexed<items_t...> indexed;

    private:
        template<
            typename ... oitems_t,
            size_t ... indexes_c>
        explicit constexpr
        tuple(
            tuple<oitems_t...> const& __other,
            indexes<indexes_c...>) :
            indexed{ __other.template get<indexes_c>()... } {}

        template<
            typename ... oitems_t,
            size_t ... indexes_c>
        explicit constexpr
        tuple(
            tuple<oitems_t...>&& __other,
            indexes<indexes_c...>) :
            indexed{ thodd::rvalue(__other.template get<indexes_c>())... } {}

    public:
        constexpr tuple() = default;

        explicit constexpr tuple(
            auto const&... __oitems) : 
            indexed{ perfect<decltype(__oitems)>(__oitems)... } {}

    public:
        template<
            typename ... oitems_t>
        constexpr tuple(
            tuple<oitems_t...> const& __other) :
            tuple{__other, make_indexes<sizeof...(items_t)>{}} {}

        template<
            typename ... oitems_t>
        constexpr tuple(
            tuple<oitems_t...>&& __other) :
            tuple{__other, make_indexes<sizeof...(items_t)>{}} {}

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
            tuple<oitems_t...> const& _other)
        {
            tuple_algorithm::assign(this->indexed, _other.indexed, make_indexes<sizeof...(items_t)>{});
            return *this;
        }

        template<
            typename ... oitems_t>
        inline tuple&
        operator = (
            tuple<oitems_t...>&& _other)
        {
            tuple_algorithm::assign(this->indexed, _other.indexed, make_indexes<sizeof...(items_t)>{});
            return *this;
        }

        template<
            typename ... oitems_t>
        inline tuple&
        operator = (
            tuple<oitems_t...>& _other)
        {
            tuple_algorithm::assign(this->indexed, _other.indexed, make_indexes<sizeof...(items_t)>{});
            return *this;
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
        -> decltype(auto)
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
        -> decltype(auto)
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
		-> decltype(auto)
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
		-> decltype(auto)
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

        template<
            typename func_t, 
            typename ... tuples_t>
        constexpr void
        foreach_join(
            func_t&& _func, 
            tuples_t&& ... __tuples)
        {
            tuple_algorithm::
            foreach_join(
                make_indexes<sizeof...(items_t)>{}, 
                this->indexed,
                perfect<func_t>(_func),
                perfect<tuples_t>(__tuples)...);
        }

        template<
            typename func_t, 
            typename ... tuples_t>
        constexpr void
        foreach_join(
            func_t&& _func, 
            tuples_t&& ... __tuples) const
        {
            tuple_algorithm::
            foreach_join(
                make_indexes<sizeof...(items_t)>{},
                this->indexed,
                perfect<func_t>(_func),
                perfect<tuples_t>(__tuples)...);
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
        return 
        tuple<items_t...>{
            perfect<items_t>(_items)...};
    }


    /// Tuple factory
    /// for reference
    /// only
    template<
        typename... items_t>
    constexpr tuple<items_t&...>
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
    constexpr auto
    perfect_as_tuple(
        items_t&&... _items)
    {
        return 
        tuple<items_t&&...>(
            perfect<items_t>(_items)...);
    }


    template<
        size_t index_c,
        typename ... items_t>
    constexpr auto
    get(
        tuple<items_t...>&& __tuple)
    -> decltype(auto)
    {
        return 
        __tuple.template get<index_c>();
    }


    template<
        size_t index_c,
        typename ... items_t>
    constexpr auto
    get(
        tuple<items_t...> const& __tuple)
    -> decltype(auto)
    {
        return 
        __tuple.template get<index_c>();
    }
    

    template<
        size_t index_c,
        typename ... items_t>
    constexpr auto
    get(
        tuple<items_t...>& __tuple)
    -> decltype(auto)
    {
        return 
        __tuple.template get<index_c>();
    }


    template<
        typename ... items_t>
    constexpr auto
    apply(
        tuple<items_t...>&& __tuple, 
        auto&& __func)
    -> decltype(auto)
    {
        return 
        __tuple.template apply(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    constexpr auto
    apply(
        tuple<items_t...> const& __tuple, 
        auto&& __func)
    -> decltype(auto)
    {
        return 
        __tuple.template apply(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    constexpr auto
    apply(
        tuple<items_t...>& __tuple, 
        auto&& __func)
    -> decltype(auto)
    {
        return 
        __tuple.template apply(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    constexpr auto
    functional_apply(
        tuple<items_t...>&& __tpl,
        auto&& __func,
        auto&&... __args)
    -> decltype(auto)
    {
        return 
        __tpl.template functional_apply(
            perfect<decltype(__func)>(__func),
            perfect<decltype(__args)>(__args)...);
    }


    template<
        typename ... items_t>
    constexpr auto
    functional_apply(
        tuple<items_t...> const& __tpl,
        auto&& __func,
        auto&&... __args)
    -> decltype(auto)
    {
        return 
        __tpl.template functional_apply(
            perfect<decltype(__func)>(__func),
            perfect<decltype(__args)>(__args)...);
    }


    template<
        typename ... items_t>
    constexpr auto
    functional_apply(
        tuple<items_t...>& __tpl,
        auto&& __func,
        auto&&... __args)
    -> decltype(auto)
    {
        return 
        __tpl.template functional_apply(
            perfect<decltype(__func)>(__func),
            perfect<decltype(__args)>(__args)...);
    }


    template<
        typename ... items_t>
    constexpr auto 
    foreach(
        tuple<items_t...>&& __tuple, 
        auto&& __func)
    -> decltype(auto)
    {
        return 
        __tuple.template foreach(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    constexpr auto 
    foreach(
        tuple<items_t...> const& __tuple, 
        auto&& __func)
    -> decltype(auto)
    {
        return
        __tuple.template foreach(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    constexpr auto 
    foreach(
        tuple<items_t...>& __tuple, 
        auto&& __func)
    -> decltype(auto)
    {
        return 
        __tuple.template foreach(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    constexpr auto 
    foreach_join(
        tuple<items_t...>&& __tuple, 
        auto&& __func, 
        auto&&... __tuples)
    -> decltype(auto)
    {
        return 
        __tuple.template foreach_join(
            perfect<decltype(__func)>(__func), 
            perfect<decltype(__tuples)>(__tuples)...);
    }


    template<
        typename ... items_t>
    constexpr auto 
    foreach_join(
        tuple<items_t...> const& __tuple, 
        auto&& __func, 
        auto&&... __tuples)
    -> decltype(auto)
    {
        return
        __tuple.template foreach_join(
            perfect<decltype(__func)>(__func), 
            perfect<decltype(__tuples)>(__tuples)...);
    }


    template<
        typename ... items_t>
    constexpr auto 
    foreach_join(
        tuple<items_t...>& __tuple, 
        auto&& __func, 
        auto&&... __tuples)
    -> decltype(auto)
    {
        return 
        __tuple.template foreach_join(
            perfect<decltype(__func)>(__func), 
            perfect<decltype(__tuples)>(__tuples)...);
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

        return 
        tpl {
            make_tuple(perfect<item1_t>(__item1)).indexed 
            + __tuple2.indexed};
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

        return  tpl{_tuple1.indexed 
                  + _tuple2.indexed};
    }


    /// Operator== that compare
    /// two tuples
    template<
        typename ... items1_t,
        typename ... items2_t>
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
        typename ... items1_t,
        typename ... items2_t>
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
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator<(
        tuple<items1_t...> const& _tuple1,
        tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.indexed < _tuple2.indexed;
    }


    /// Operator<= that compare
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator<=(
        tuple<items1_t...> const& _tuple1,
        tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.indexed <= _tuple2.indexed;
    }


    template<
        typename ... items1_t,
        typename ... items2_t>
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
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator>=(
        tuple<items1_t...> const& _tuple1,
        tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.indexed >= _tuple2.indexed;
    }
}

#endif