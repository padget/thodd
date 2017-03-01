#ifndef __THODD_TUPLE_INDEXED_HPP__
#  define __THODD_TUPLE_INDEXED_HPP__

#  include <thodd/meta.hpp>
#  include <thodd/law.hpp>
#  include <thodd/tuple_element.hpp>
#  include <thodd/tuple_functional.hpp>

/**
    template<
        size_t min_c, 
        size_t max_c, 
        size_t ... indexes_c, 
        typename ... items_t>
    constexpr auto
    extract(tuple_indexed<indexes<indexes_c...>, items_t...> const& __t)
    {
        return make_tuple(thodd::get<min_c>(__t), ..., thodd::get<max_c>(__t));
    }

*/

namespace thodd
{
    template<
        typename indexes_t,
        typename ... items_t>
    struct tuple_indexed;


    template<
        size_t... indexes_c,
        typename ... items_t>
    struct tuple_indexed<indexes<indexes_c...>, items_t...>:
        public tuple_element<items_t, indexes_c>...
    {
    public:
        constexpr tuple_indexed() = default;


        template<
            typename ... oitems_t>
        explicit constexpr
        tuple_indexed(
            oitems_t&&... __items) :
            tuple_element<items_t, indexes_c>
            { perfect<oitems_t>(__items) }... {}


    public:
        template<
            typename ... oitems_t>
        constexpr
        tuple_indexed(
            tuple_indexed<indexes<indexes_c...>, oitems_t...>&& __other) :
            tuple_element<items_t, indexes_c>
            { thodd::rvalue(thodd::get<indexes_c>(__other)) }... {}


        template<
            typename ... oitems_t>
        constexpr
        tuple_indexed(
            tuple_indexed<indexes<indexes_c...>, oitems_t...> const& __other) :
            tuple_element<items_t, indexes_c>
            { thodd::get<indexes_c>(__other) }... {}


        template<
            typename ... oitems_t>
        constexpr
        tuple_indexed(
            tuple_indexed<indexes<indexes_c...>, oitems_t...>& __other) :
            tuple_indexed<items_t...>
            { const_cast<tuple_indexed<items_t...> const&>(__other) } {}        


    public:
        template<
            typename ... oitems_t>
        constexpr bool
        operator == (
            tuple_indexed<indexes<indexes_c...>, oitems_t...> const& __other) const
        {
            if(this == &__other)
                return true;

            bool __res{true};
            repeat{(__res &= thodd::get<indexes_c>(*this) == thodd::get<indexes_c>(__other), 0)...};
            
            return __res;
        }


        template<
            typename ... oitems_t>
        constexpr bool
        operator != (
            tuple_indexed<indexes<indexes_c...>, oitems_t...> const& __other) const
        {
            return  
            !((*this) == __other);
        }


        template<
            typename ... oitems_t>
        constexpr bool
        operator < (
            tuple_indexed<indexes<indexes_c...>, oitems_t...> const& __other) const
        {
            if(this == &__other)
                return false;

            bool __res{true};
            repeat{ (__res &= thodd::get<indexes_c>(*this) < thodd::get<indexes_c>(__other), 0)... };
            
            return __res;
        }


        template<
            typename ... oitems_t>
        constexpr bool
        operator <= (
            tuple_indexed<indexes<indexes_c...>, oitems_t...> const& __other) const
        {
            return 
            ((*this) < __other) 
            || ((*this) == __other);
        }


        template<
            typename ... oitems_t>
        constexpr bool
        operator > (
            tuple_indexed<indexes<indexes_c...>, oitems_t...> const& __other) const
        {
            return  
            !((*this) <= __other);
        }


        template<
            typename ... oitems_t>
        constexpr bool
        operator >= (
            tuple_indexed<indexes<indexes_c...>, oitems_t...> const& __other) const
        {
            return  
            !((*this) < __other);
        }


        template<
            typename ... oitems_t, 
            size_t ... oindexes_c>
        constexpr auto 
        operator + (
            tuple_indexed<indexes<oindexes_c...>, oitems_t...> const& __other) const &
        {
            using indexes_t = make_indexes<sizeof...(items_t) + sizeof...(oitems_t)>;

            return 
            tuple_indexed<indexes_t, items_t..., oitems_t...>
            { thodd::get<indexes_c>(*this)..., 
              thodd::get<oindexes_c>(__other)... };
        }


        template<
            typename ... oitems_t, 
            size_t ... oindexes_c>
        constexpr auto 
        operator + (
            tuple_indexed<indexes<oindexes_c...>, oitems_t...>&& __other) const &
        {
            using indexes_t = make_indexes<sizeof...(items_t) + sizeof...(oitems_t)>;

            return 
            tuple_indexed<indexes_t, items_t..., oitems_t...>
            { thodd::get<indexes_c>(*this)..., 
              thodd::rvalue(thodd::get<oindexes_c>(__other))... };
        }


        template<
            typename ... oitems_t, 
            size_t ... oindexes_c>
        constexpr auto 
        operator + (
            tuple_indexed<indexes<oindexes_c...>, oitems_t...> const& __other) &&
        {
            using indexes_t = make_indexes<sizeof...(items_t) + sizeof...(oitems_t)>;

            return 
            tuple_indexed<indexes_t, items_t..., oitems_t...>
            { thodd::rvalue(thodd::get<indexes_c>(*this))..., 
              thodd::get<oindexes_c>(__other)... };
        }


        template<
            typename ... oitems_t, 
            size_t ... oindexes_c>
        constexpr auto 
        operator + (
            tuple_indexed<indexes<oindexes_c...>, oitems_t...> && __other) &&
        {
            using indexes_t = make_indexes<sizeof...(items_t) + sizeof...(oitems_t)>;

            return 
            tuple_indexed<indexes_t, items_t..., oitems_t...>
            { thodd::rvalue(thodd::get<indexes_c>(*this))..., 
              thodd::rvalue(thodd::get<oindexes_c>(__other))... };
        }


    public:
        constexpr auto
        apply(
            auto&& __func) &
        -> decltype(auto)
        {
            return
            perfect<decltype(__func)>(__func)(
                thodd::get<indexes_c>(*this)...);
        }


        constexpr auto
        apply(
            auto&& __func) const &
        -> decltype(auto)
        {
            return
            perfect<decltype(__func)>(__func)(
                thodd::get<indexes_c>(*this)...);
        }


        constexpr auto
        apply(
            auto&& __func) &&
        -> decltype(auto)
        {
            return
            perfect<decltype(__func)>(__func)(
                thodd::rvalue(
                    thodd::get<indexes_c>(*this))...);
        } 


        constexpr auto
        foreach(
            auto&& __func) &
        -> decltype(auto)
        {
            repeat{ (perfect<decltype(__func)>(__func)(
                thodd::get<indexes_c>(*this)), 0)... };
        }


        constexpr auto
        foreach(
            auto&& __func) const &
        -> decltype(auto)
        {
            repeat{ (perfect<decltype(__func)>(__func)(
                thodd::get<indexes_c>(*this)), 0)... };
        }

        
        constexpr auto
        foreach(
            auto&& __func) &&
        -> decltype(auto)
        {
            repeat{ (perfect<decltype(__func)>(__func)(
                thodd::rvalue(
                    thodd::get<indexes_c>(*this))), 0)... };
        }

    };


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
}


#endif