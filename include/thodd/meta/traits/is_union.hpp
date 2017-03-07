#ifndef __THODD_META_TRAITS_IS_UNION_HPP__
#  define __THODD_META_TRAITS_IS_UNION_HPP__


namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_union(
       type_t const&) 
    {
        return
        __is_union(type_t);
    }
}

#endif