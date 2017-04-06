#ifndef __THODD_TUPLE_INDEXED_HPP__
#  define __THODD_TUPLE_INDEXED_HPP__

#  include <thodd/tuple/tuple_element.hpp>
#  include <thodd/tuple/functional.hpp>

#  include <thodd/core/sequence.hpp>
#  include <thodd/core/expand.hpp>
#  include <thodd/core/get.hpp>
#  include <thodd/core/integral.hpp>
#  include <thodd/core/and.hpp>

namespace thodd
{
    template<
        typename indexes_t,
        typename ... items_t>
    struct tuple_indexed;


    template<
        size_t max_c>
    using make_indexes = 
        thodd::make_rsequence_t<size_t, 0u, max_c - 1u>;


    template<
        size_t ... indexes_c,
        typename ... items_t>
    struct tuple_indexed<sequence<size_t, indexes_c...>, items_t...>:
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
            { perfect<oitems_t>(__items) } ... {}


    public:
        template<
            typename ... oitems_t>
        constexpr
        tuple_indexed(
            tuple_indexed<sequence<size_t, indexes_c...>, oitems_t...>&& __other) :
            tuple_element<items_t, indexes_c>
            { thodd::rvalue(thodd::get<indexes_c>(__other)) } ... {}


        template<
            typename ... oitems_t>
        constexpr
        tuple_indexed(
            tuple_indexed<sequence<size_t, indexes_c...>, oitems_t...> const& __other) :
            tuple_element<items_t, indexes_c>
            { thodd::get<indexes_c>(__other) } ... {}


        template<
            typename ... oitems_t>
        constexpr
        tuple_indexed(
            tuple_indexed<sequence<size_t, indexes_c...>, oitems_t...>& __other) :
            tuple_indexed<items_t...>
            { const_cast<tuple_indexed<items_t...> const&>(__other) } {}        



    public:
        
        template<
            typename ... oitems_t>
        constexpr bool
        operator == (
            tuple_indexed<sequence<size_t, indexes_c...>, oitems_t...> const& __other) const
        {
            if(this == &__other)
                return true;

            bool __res{true};
            expand{
                ((__res &= thodd::get<indexes_c>(*this) 
                       == thodd::get<indexes_c>(__other)), 0)...};
            
            return __res;
        }


        template<
            typename ... oitems_t>
        constexpr bool
        operator != (
            tuple_indexed<sequence<size_t, indexes_c...>, oitems_t...> const& __other) const
        {
            return  
            !((*this) == __other);
        }


        template<
            typename ... oitems_t>
        constexpr bool
        operator < (
            tuple_indexed<sequence<size_t, indexes_c...>, oitems_t...> const& __other) const
        {
            if(this == &__other)
                return false;

            bool __res{true};
            expand{ 
                ((__res &= thodd::get<indexes_c>(*this) 
                        < thodd::get<indexes_c>(__other)), 0)...};
            
            return __res;
        }


        template<
            typename ... oitems_t>
        constexpr bool
        operator <= (
            tuple_indexed<sequence<size_t, indexes_c...>, oitems_t...> const& __other) const
        {
            return 
            ((*this) < __other) 
            || ((*this) == __other);
        }


        template<
            typename ... oitems_t>
        constexpr bool
        operator > (
            tuple_indexed<sequence<size_t, indexes_c...>, oitems_t...> const& __other) const
        {
            return  
            !((*this) <= __other);
        }


        template<
            typename ... oitems_t>
        constexpr bool
        operator >= (
            tuple_indexed<sequence<size_t, indexes_c...>, oitems_t...> const& __other) const
        {
            return  
            !((*this) < __other);
        }


        template<
            typename ... oitems_t, 
            size_t ... oindexes_c>
        constexpr auto 
        operator + (
            tuple_indexed<sequence<size_t, oindexes_c...>, oitems_t...> const& __other) const &
        {
            using indexes_t = 
                make_indexes<
                    sizeof...(items_t) 
                    + sizeof...(oitems_t)>;

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
            tuple_indexed<sequence<size_t, oindexes_c...>, oitems_t...>&& __other) const &
        {
            using indexes_t = 
                make_indexes<
                    sizeof...(items_t) 
                    + sizeof...(oitems_t)>;

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
            tuple_indexed<sequence<size_t, oindexes_c...>, oitems_t...> const& __other) &&
        {
            using indexes_t = 
                make_indexes<
                    sizeof...(items_t) 
                    + sizeof...(oitems_t)>;

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
            tuple_indexed<sequence<size_t, oindexes_c...>, oitems_t...> && __other) &&
        {
            using indexes_t = 
                make_indexes<
                    sizeof...(items_t) 
                    + sizeof...(oitems_t)>;

            return 
            tuple_indexed<indexes_t, items_t..., oitems_t...>
            { thodd::rvalue(thodd::get<indexes_c>(*this))..., 
              thodd::rvalue(thodd::get<oindexes_c>(__other))... };
        }


    public:
        template<
            size_t ... oindexes_c>
        constexpr auto 
        extract(
            sequence<size_t, oindexes_c...>) const
        {
            static_assert(
                sizeof...(oindexes_c) <= sizeof...(items_t), 
                "The size of the extracted set of items can't "
                "be bigger than the number items in the origin");


            static_assert(
                and_c((oindexes_c < sizeof...(items_t))...),
                "Each index must be inferior than the max " 
                "index of the container");
            

            constexpr 
            tuple_indexed<
                make_indexes<
                    sizeof...(indexes_c)>, 
                meta::type_<items_t>...> __types; 
         
            return
            tuple_indexed<
                make_indexes<sizeof...(oindexes_c)>, 
                meta::__type<
                    meta::decay_t<
                        decltype(thodd::get<oindexes_c>(__types))>>...>
            { thodd::get<oindexes_c>(*this)... };
        }


        template<
            size_t min_c, 
            size_t max_c>
        constexpr auto 
        extract() &
        {
            return 
            extract(
                make_rsequence_t<size_t, min_c, max_c>{});
        }


        template<
            size_t min_c, 
            size_t max_c>
        constexpr auto 
        extract() const &
        {
            return 
            extract(
                make_rsequence_t<size_t, min_c, max_c>{});
        }


        template<
            size_t min_c, 
            size_t max_c>
        constexpr auto 
        extract() &&
        {
            return 
            extract(
                make_rsequence_t<size_t, min_c, max_c>{});
        }


        constexpr auto
        apply(
            auto&& __func) &
        -> decltype(auto)
        {
            return
            perfect<decltype(__func)>(__func)
            (thodd::get<indexes_c>(*this)...);
        }


        constexpr auto
        apply(
            auto&& __func) const &
        -> decltype(auto)
        {
            return
            perfect<decltype(__func)>(__func)
            (thodd::get<indexes_c>(*this)...);
        }


        constexpr auto
        apply(
            auto&& __func) &&
        -> decltype(auto)
        {
            return
            perfect<decltype(__func)>(__func)
            (thodd::rvalue(thodd::get<indexes_c>(*this))...);
        } 


        constexpr auto
        functional_apply(
            auto&& __func,
            auto&& ... __args) &
        -> decltype(auto)
        {
            return 
            perfect<decltype(__func)>(__func)
            (thodd::get<indexes_c>(*this)(
                perfect<decltype(__args)>(__args)...)...);
        }

        
        constexpr auto
        functional_apply(
            auto&& __func,
            auto&& ... __args) const &
        -> decltype(auto)
        {
            return 
            perfect<decltype(__func)>(__func)
            (thodd::get<indexes_c>(*this)(
                perfect<decltype(__args)>(__args)...)...);
        }


        constexpr auto
        functional_apply(
            auto&& __func,
            auto&& ... __args) &&
        -> decltype(auto)
        {
            return 
            perfect<decltype(__func)>(__func)
            (thodd::rvalue(thodd::get<indexes_c>(*this))(
                perfect<decltype(__args)>(__args)...)...);
        }


        constexpr auto
        foreach(
            auto&& __func) &
        -> decltype(auto)
        {
            expand{(perfect<decltype(__func)>(__func)(
                thodd::get<indexes_c>(*this)), 0)...};
        }


        constexpr auto
        foreach(
            auto&& __func) const &
        -> decltype(auto)
        {
            expand{(perfect<decltype(__func)>(__func)(
                thodd::get<indexes_c>(*this)), 0)...};
        }

        
        constexpr auto
        foreach(
            auto&& __func) &&
        -> decltype(auto)
        {
            expand{(perfect<decltype(__func)>(__func)(
                thodd::rvalue(
                    thodd::get<indexes_c>(*this))), 0)...};
        }


        template<
            size_t index_c>
        constexpr auto
        foreach_join(
            auto&& __func, 
            auto&&... __others) &
        -> decltype(auto) 
        {
            return 
            perfect<decltype(__func)>(__func)(
                thodd::get<index_c>(*this),
                thodd::get<index_c>(perfect<decltype(__others)>(__others))...);
        }


        template<
            size_t index_c>
        constexpr auto
        foreach_join(
            auto&& __func, 
            auto&&... __others) const &
        -> decltype(auto)
        {
            return 
            perfect<decltype(__func)>(__func)(
                thodd::get<index_c>(*this),
                thodd::get<index_c>(perfect<decltype(__others)>(__others))...);
        }


        template<
            size_t index_c>
        constexpr auto
        foreach_join(
            auto&& __func, 
            auto&&... __others) &&
        -> decltype(auto)
        {
            return 
            perfect<decltype(__func)>(__func)(
                thodd::get<index_c>(*this),
                thodd::get<index_c>(perfect<decltype(__others)>(__others))...);
        }


        constexpr auto
        foreach_join(
            auto&& __func,
            auto&&... __others) &
        -> decltype(auto)
        {
            expand {(
                foreach_join<indexes_c>(
                    perfect<decltype(__func)>(__func),  
                    perfect<decltype(__others)>(__others)...), 0)...};
        }


        constexpr auto
        foreach_join(
            auto&& __func,
            auto&&... __others) const &
        -> decltype(auto)
        {
            expand {(
                foreach_join<indexes_c>(
                    perfect<decltype(__func)>(__func), 
                    perfect<decltype(__others)>(__others)...), 0)...};
        }


        constexpr auto
        foreach_join(
            auto&& __func,
            auto&&... __others) &&
        -> decltype(auto)
        {
            expand {(
                foreach_join<indexes_c>(
                    perfect<decltype(__func)>(__func), 
                    perfect<decltype(__others)>(__others)...), 0)...};
        }
    };
}

#endif