#ifndef __THODD_META_TRAITS_CONCEPT_HPP__
#  define __THODD_META_TRAITS_CONCEPT_HPP__

namespace 
thodd::meta
{
    template<
        typename type_t, 
        typename otype_t>
    concept bool is_same2 = std::is_same_v<type_t, otype_t> ;

    template<
        typename base_t, 
        typename derived_t>
    concept bool is_base_of2 = std::is_base_of_v<base_t, derived_t> ;

    template<
        typename type_t,
        typename ... types_t>
    concept bool is_one_of2 = thodd::or_c(is_same2<type_t, types_t>...) ;

    template<
        typename type_t>
    concept bool is_floating_point2 = is_one_of2<type_t, types_t...>;
}

#endif