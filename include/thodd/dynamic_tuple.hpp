#ifndef __THODD_DYNAMIC_TUPLE_HPP__
#  define __THODD_DYNAMIC_TUPLE_HPP__

#  include <thodd/meta.hpp>
#  include <thodd/law.hpp>
#  include <thodd/tuple.hpp>
#  include <thodd/functional.hpp>

namespace thodd
{
    template<
        typename ... items_t>
    struct dynamic_tuple
    {
        using tuple_t   = thodd::tuple<items_t*...>; 

        tuple_t storage{(items_t*)nullptr...};

    private:
        template<
            typename ... oitems_t,
            size_t ... indexes_c>
        dynamic_tuple(
            dynamic_tuple<oitems_t...>&& __other,
            indexes<indexes_c...>) :
            storage( (thodd::rvalue(__other).template get<indexes_c>() != nullptr ? 
                      new oitems_t{ thodd::rvalue(*thodd::rvalue(__other).template get<indexes_c>()) } : 
                      (oitems_t*) nullptr)... ) {}
        
        template<
            typename ... oitems_t,
            size_t ... indexes_c>
        dynamic_tuple(
            dynamic_tuple<oitems_t...> const& __other,
            indexes<indexes_c...>) :
            storage( (__other.template get<indexes_c>() != nullptr ? 
                      new oitems_t{ *__other.template get<indexes_c>() } : 
                      (oitems_t*) nullptr)... ) {}
        
    public:
        dynamic_tuple() = default; 


        ~dynamic_tuple()
        {
            thodd::foreach(
                storage, 
                thodd::delete_);
        }
         
        explicit 
        dynamic_tuple(
		    auto&&... __oitems) : 
            storage( new meta::remove_pointer<meta::decay<decltype(__oitems)>>{perfect<decltype(__oitems)>(__oitems)}... ) {}

        template<
            typename ... oitems_t>
        dynamic_tuple(
            dynamic_tuple<oitems_t...> const& __other) :
            dynamic_tuple( __other, make_indexes<sizeof...(oitems_t)>{} ) {}

        template<
            typename ... oitems_t>
        dynamic_tuple(
            dynamic_tuple<oitems_t...>&& __other) :
            dynamic_tuple( thodd::rvalue(__other), make_indexes<sizeof...(oitems_t)>{} ) {}

        template<
            typename ... oitems_t>
        dynamic_tuple(
            dynamic_tuple<oitems_t...>& __other) :
            dynamic_tuple( const_cast<dynamic_tuple<oitems_t...> const&>(__other) ) {}

    public:
        template<
            typename ... oitems_t>
        inline dynamic_tuple&
        operator = (
            dynamic_tuple<oitems_t...> const& __other)
        {
            storage = __other.storage;
            return *this;
        }

        template<
            typename ... oitems_t>
        inline dynamic_tuple&
        operator = (
            dynamic_tuple<oitems_t...>&& __other)
        {
            storage = __other.storage;
            return *this;
        }

        template<
            typename ... oitems_t>
        inline dynamic_tuple&
        operator = (
            dynamic_tuple<oitems_t...>& __other)
        {
            storage = __other.storage;
            return *this;
        }

    
    public:
        template<
            size_t index_c>
        inline auto
        get()
        -> decltype(auto)
        {
            return 
            thodd::get<index_c>(storage);
        }
        
        template<
            size_t index_c>
        inline auto
        get() const
        -> decltype(auto)
        {
            return 
            thodd::get<index_c>(storage);
        }


        inline auto
        apply(
            auto&& __func)
        -> decltype(auto)
        {
            return 
            thodd::apply(
                storage, 
                perfect<decltype(__func)>(__func));
        }


        inline auto
        apply(
            auto&& __func) const
        -> decltype(auto)
        {
            return 
            thodd::apply(
                storage, 
                perfect<decltype(__func)>(__func));
        }


		inline auto
		functional_apply(
			auto&& __func,
			auto&&... __args)
		-> decltype(auto)
		{
			return 
            thodd::functional_apply(
                storage, 
                perfect<decltype(__func)>(__func),
                perfect<decltype(__args)>(__args)...);
		}

        
        inline auto
		functional_apply(
			auto&& __func,
			auto&&... __args) const
		-> decltype(auto)
		{
			return 
            thodd::functional_apply(
                storage, 
                perfect<decltype(__func)>(__func),
                perfect<decltype(__args)>(__args)...);
		}


        inline auto
        foreach(
            auto&& __func)
        -> decltype(auto)
        {
            return 
            thodd::foreach(
                storage, 
                perfect<decltype(__func)>(__func));
        }


        inline auto
        foreach(
            auto&& __func) const
        -> decltype(auto)
        {
            return 
            thodd::foreach(
                storage, 
                perfect<decltype(__func)>(__func));
        }


        inline auto
        foreach_join(
            auto&& __func, 
            auto&& ... __tuples)
        -> decltype(auto)
        {
            return 
            thodd::foreach_join(
                storage,
                perfect<decltype(__func)>(__func),
                perfect<decltype(__tuples)>(__tuples)...);
        }

        
        inline auto
        foreach_join(
            auto&& __func, 
            auto&& ... __tuples) const 
        -> decltype(auto)
        {
            return 
            thodd::foreach_join(
                storage,
                perfect<decltype(__func)>(__func),
                perfect<decltype(__tuples)>(__tuples)...);
        }
    };


    template<
        size_t index_c, 
        typename ... items_t>
    inline auto
    get(
        dynamic_tuple<items_t...>&& __dt)
    -> decltype(auto)
    {
        return 
        __dt.template get<index_c>();
    }

    
    template<
        size_t index_c, 
        typename ... items_t>
    inline auto
    get(
        dynamic_tuple<items_t...> const& __dt)
    -> decltype(auto)
    {
        return 
        __dt.template get<index_c>();
    }

    
    template<
        size_t index_c, 
        typename ... items_t>
    inline auto
    get(
        dynamic_tuple<items_t...>& __dt)
    -> decltype(auto)
    {
        return 
        __dt.template get<index_c>();
    }
    
    
    template<
        typename ... items_t>
    inline auto
    apply(
        dynamic_tuple<items_t...>&& __dt, 
        auto&& __func)
    -> decltype(auto)
    {
        return 
        __dt.template apply(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    inline auto
    apply(
        dynamic_tuple<items_t...> const& __dt, 
        auto&& __func)
    -> decltype(auto)
    {
        return 
        __dt.template apply(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    inline auto
    apply(
        dynamic_tuple<items_t...>& __dt, 
        auto&& __func)
    -> decltype(auto)
    {
        return 
        __dt.template apply(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    inline auto
    functional_apply(
        dynamic_tuple<items_t...>&& __tpl,
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
    inline auto
    functional_apply(
        dynamic_tuple<items_t...> const& __tpl,
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
    inline auto
    functional_apply(
        dynamic_tuple<items_t...>& __tpl,
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
    inline auto 
    foreach(
        dynamic_tuple<items_t...>&& __dt, 
        auto&& __func)
    -> decltype(auto)
    {
        return 
        __dt.template foreach(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    inline auto 
    foreach(
        dynamic_tuple<items_t...> const& __dt, 
        auto&& __func)
    -> decltype(auto)
    {
        return
        __dt.template foreach(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    inline auto 
    foreach(
        dynamic_tuple<items_t...>& __dt, 
        auto&& __func)
    -> decltype(auto)
    {
        return 
        __dt.template foreach(
            perfect<decltype(__func)>(__func));
    }


    template<
        typename ... items_t>
    inline auto 
    foreach_join(
        dynamic_tuple<items_t...>&& __dt, 
        auto&& __func, 
        auto&&... __tuples)
    -> decltype(auto)
    {
        return 
        __dt.template foreach_join(
            perfect<decltype(__func)>(__func), 
            perfect<decltype(__tuples)>(__tuples)...);
    }


    template<
        typename ... items_t>
    inline auto 
    foreach_join(
        dynamic_tuple<items_t...> const& __dt, 
        auto&& __func, 
        auto&&... __tuples)
    -> decltype(auto)
    {
        return
        __dt.template foreach_join(
            perfect<decltype(__func)>(__func), 
            perfect<decltype(__tuples)>(__tuples)...);
    }


    template<
        typename ... items_t>
    inline auto 
    foreach_join(
        dynamic_tuple<items_t...>& __dt, 
        auto&& __func, 
        auto&&... __tuples)
    -> decltype(auto)
    {
        return 
        __dt.template foreach_join(
            perfect<decltype(__func)>(__func), 
            perfect<decltype(__tuples)>(__tuples)...);
    }

    inline auto 
    make_dynamic_tuple(
        auto&&... __items)
    {
        return 
        dynamic_tuple<meta::decay<decltype(__items)>...>
        { perfect<decltype(__items)>(__items)... };
    }


     /// Operator+ that concat
    /// two tuples
    template<
        typename ... items1_t,
        typename item2_t>
    constexpr auto
    operator + (
        dynamic_tuple<items1_t...> const& __tuple1,
        item2_t&& __item2)
    {
        using tpl = dynamic_tuple<items1_t..., item2_t>;

        return 
        tpl
        { thodd::rvalue(__tuple1.storage + make_dynamic_tuple(perfect<item2_t>(__item2)).storage) };
    }


    /// Operator+ that concat
    /// two tuples
    template<
        typename item1_t,
        typename ... items2_t>
    constexpr auto
    operator + (
        item1_t&& __item1,
        dynamic_tuple<items2_t...> const& __tuple2)
    {
        using tpl = dynamic_tuple<item1_t, items2_t...>;

        return 
        tpl {
            thodd::rvalue(make_dynamic_tuple(perfect<item1_t>(__item1)).storage 
            + __tuple2.storage)};
    }


    /// Operator+ that concat
    /// two tuples
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr auto
    operator + (
        dynamic_tuple<items1_t...> const& _tuple1,
        dynamic_tuple<items2_t...> const& _tuple2)
    {
        using tpl = dynamic_tuple<items1_t..., items2_t...>;

        return  tpl{thodd::rvalue(_tuple1.storage 
                  + _tuple2.storage)};
    }



    /// Operator== that compare
    /// two tuples
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator==(
        dynamic_tuple<items1_t...> const& _tuple1,
        dynamic_tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.storage == _tuple2.storage;
    }


    /// Operator!= that compare
    /// two tuples
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator!=(
        dynamic_tuple<items1_t...> const& _tuple1,
        dynamic_tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.storage != _tuple2.storage;
    }


    /// Operator< that compare
    /// two tuples
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator<(
        dynamic_tuple<items1_t...> const& _tuple1,
        dynamic_tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.storage < _tuple2.storage;
    }


    /// Operator<= that compare
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator<=(
        dynamic_tuple<items1_t...> const& _tuple1,
        dynamic_tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.storage <= _tuple2.storage;
    }


    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator>(
        dynamic_tuple<items1_t...> const& _tuple1,
        dynamic_tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.storage > _tuple2.storage;
    }


    /// Operator>= that compare
    /// two tuples
    template<
        typename ... items1_t,
        typename ... items2_t>
    constexpr bool
    operator>=(
        dynamic_tuple<items1_t...> const& _tuple1,
        dynamic_tuple<items2_t...> const& _tuple2)
    {
        return _tuple1.storage >= _tuple2.storage;
    }
}

#endif 