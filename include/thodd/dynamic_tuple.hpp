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
    class dynamic_tuple
    {
        template<
            typename item_t>
        using pointer_t = item_t*;
        using tuple_t   = thodd::tuple<pointer_t<items_t>...>; 

        tuple_t storage;

    public:
        dynamic_tuple() = default; 

        dynamic_tuple(dynamic_tuple&&) = default;
        dynamic_tuple(dynamic_tuple const&) = default;

        ~dynamic_tuple()
        {
            thodd::foreach(
                storage, 
                thodd::delete_);
        }

    public:
        dynamic_tuple& 
        operator = (
            dynamic_tuple&&) = default;
        
        dynamic_tuple& 
        operator = (
            dynamic_tuple const&) = default;

    
    public:
        template<
            size_t index_c>
        constexpr auto
        get()
        -> decltype(auto)
        {
            return 
            *thodd::get<index_c>(storage);
        }
        
        template<
            size_t index_c>
        constexpr auto
        get() const
        -> decltype(auto)
        {
            return 
            *thodd::get<index_c>(storage);
        }


        constexpr auto
        apply(
            auto&& __func)
        -> decltype(auto)
        {
            return 
            thodd::apply(
                storage, 
                perfect<decltype(__func)>(__func));
        }


        constexpr auto
        apply(
            auto&& __func) const
        -> decltype(auto)
        {
            return 
            thodd::apply(
                storage, 
                perfect<decltype(__func)>(__func));
        }


		constexpr auto
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

        
        constexpr auto
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


        constexpr auto
        foreach(
            auto&& __func)
        -> decltype(auto)
        {
            return 
            thodd::foreach(
                storage, 
                perfect<decltype(__func)>(__func));
        }


        constexpr auto
        foreach(
            auto&& __func) const
        -> decltype(auto)
        {
            return 
            thodd::foreach(
                storage, 
                perfect<decltype(__func)>(__func));
        }


        constexpr auto
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

        
        constexpr auto
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
        *__dt.template get<index_c>();
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
        *__dt.template get<index_c>();
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
        *__dt.template get<index_c>();
    }
    
    
    template<
        typename ... items_t>
    constexpr auto
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
    constexpr auto
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
    constexpr auto
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
    constexpr auto
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
    constexpr auto
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
    constexpr auto
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
    constexpr auto 
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
    constexpr auto 
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
    constexpr auto 
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
    constexpr auto 
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
    constexpr auto 
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
    constexpr auto 
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
}

#endif 