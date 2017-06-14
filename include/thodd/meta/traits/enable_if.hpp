#ifndef __THODD_META_TRAITS_ENABLE_IF_HPP__
#  define __THODD_META_TRAITS_ENABLE_IF_HPP__

namespace 
thodd::meta 
{
    template<
        bool test_c, 
        typename type_t>
    struct enable_if ;

    template<
        typename type_t>
    struct enable_if<true, type_t>
    {
        using type = type_t ;
    } ;

    template<
        bool test_c,
        typename type_t = void>
    using enable_if_t = typename enable_if<test_c, type_t>::type ;
}


#endif