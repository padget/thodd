#ifndef __THODD_DYNAMIC_TUPLE_HPP__
#  define __THODD_DYNAMIC_TUPLE_HPP__

#  include <thodd/tuple/tuple.hpp>
#  include <thodd/functional/functional.hpp>

namespace thodd
{
    template<
        typename ... items_t>
    struct dynamic_tuple : 
        public thodd::tuple<items_t*...>
    {
    public:
        using base_t = thodd::tuple<items_t*...>;

       template<
            typename ... oitems_t,
            size_t ... indexes_c>
        dynamic_tuple(
            dynamic_tuple<oitems_t...>&& __other,
            indexes<indexes_c...>) :
            base_t( (thodd::get<indexes_c>(thodd::rvalue(__other)) != nullptr ? 
                      new oitems_t{ thodd::rvalue(*thodd::get<indexes_c>(thodd::rvalue(__other))) } : 
                      (oitems_t*) nullptr)... ) {}
        
        template<
            typename ... oitems_t,
            size_t ... indexes_c>
        dynamic_tuple(
            dynamic_tuple<oitems_t...> const& __other,
            indexes<indexes_c...>) :
            base_t( (thodd::get<indexes_c>(__other) != nullptr ? 
                      new oitems_t{ *thodd::get<indexes_c>(__other) } : 
                      (oitems_t*) nullptr)... ) {}

                     
        
    public:
        dynamic_tuple() : 
            base_t{ ((items_t*) nullptr)... } {}


        ~dynamic_tuple()
        {
            thodd::foreach(
                *this, 
                thodd::delete_);
        }
         
        explicit 
        dynamic_tuple(
		    auto&&... __oitems) : 
            base_t( new meta::decay<decltype(__oitems)>{ perfect<decltype(__oitems)>(__oitems) }... ) {}
    
    
    public:
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
            this->base_t::operator = (__other);
            return *this;
        }


        template<
            typename ... oitems_t>
        inline dynamic_tuple&
        operator = (
            dynamic_tuple<oitems_t...>&& __other)
        {
            this->base_t::operator = (__other);
            return *this;
        }


        template<
            typename ... oitems_t>
        inline dynamic_tuple&
        operator = (
            dynamic_tuple<oitems_t...>& __other)
        {
            return *this = const_cast<dynamic_tuple<oitems_t...> const&>(__other);
        }       
    };


    template<
        typename type_t>
    constexpr auto 
    is_dynamic_tuple(
        type_<type_t> const&)
    {
        return false;
    }


    template<
        typename ... items_t>
    constexpr auto
    is_dynamic_tuple(
        type_<dynamic_tuple<items_t...>> const&)
    {
        return true;
    }


    inline auto 
    make_dynamic_tuple(
        auto&&... __items)
    {
        return 
        dynamic_tuple<meta::decay<decltype(__items)>...>
        { perfect<decltype(__items)>(__items)... };
    }
}

#endif 