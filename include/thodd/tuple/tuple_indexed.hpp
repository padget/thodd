#ifndef __THODD_TUPLE_INDEXED_HPP__
#  define __THODD_TUPLE_INDEXED_HPP__

#  include <thodd/tuple/tuple_element.hpp>
#  include <thodd/tuple/functional.hpp>

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
            repeat{(__res &= thodd::get<indexes_c>(*this) 
                             == thodd::get<indexes_c>(__other), 0)...};
            
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
            repeat{ (__res &= thodd::get<indexes_c>(*this) 
                              < thodd::get<indexes_c>(__other), 0)... };
            
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
        functional_apply(
            auto&& __func,
            auto&& ... __args) &
        -> decltype(auto)
        {
            return 
            perfect<decltype(__func)>(__func)(
                thodd::get<indexes_c>(*this)(
                    perfect<decltype(__args)>(__args)...)...);
        }

        
        constexpr auto
        functional_apply(
            auto&& __func,
            auto&& ... __args) const &
        -> decltype(auto)
        {
            return 
            perfect<decltype(__func)>(__func)(
                thodd::get<indexes_c>(*this)(
                    perfect<decltype(__args)>(__args)...)...);
        }


        constexpr auto
        functional_apply(
            auto&& __func,
            auto&& ... __args) &&
        -> decltype(auto)
        {
            return 
            perfect<decltype(__func)>(__func)(
                thodd::rvalue(thodd::get<indexes_c>(*this))(
                    perfect<decltype(__args)>(__args)...)...);
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


        constexpr auto
        foreach_join(
            auto&& __func,
            auto&& __other) &
        -> decltype(auto)
        {
            repeat{(perfect<decltype(__func)>(__func)(
                thodd::get<indexes_c>(*this),
                thodd::get<indexes_c>(
                    perfect<decltype(__other)>(__other))), 0)...};
        }


        constexpr auto
        foreach_join(
            auto&& __func,
            auto&& __other) const &
        -> decltype(auto)
        {
            repeat{(perfect<decltype(__func)>(__func)(
                thodd::get<indexes_c>(*this),
                thodd::get<indexes_c>(
                    perfect<decltype(__other)>(__other))), 0)...};
        }


        constexpr auto
        foreach_join(
            auto&& __func,
            auto&& __other) &&
        -> decltype(auto)
        {
            repeat{(perfect<decltype(__func)>(__func)(
                thodd::rvalue(thodd::get<indexes_c>(*this)),
                thodd::get<indexes_c>(
                    perfect<decltype(__other)>(__other))), 0)...};
        }
    };
}

#endif