#ifndef __THODD_META_TRAITS_REQUIRE_HPP__
#  define __THODD_META_TRAITS_REQUIRE_HPP__

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta 
{
    template<
        bool test_c, 
        typename type_t>
    struct require ;

    template<
        typename type_t>
    struct require<true, type_t>
    {
        using type = type_t ;
    } ;

    template<
        bool test_c,
        typename type_t = void>
    using require_t = typename require<test_c, type_t>::type ;
    
}


#endif