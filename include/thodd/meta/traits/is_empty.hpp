#ifndef __THODD_META_TRAITS_IS_EMPTY_HPP__
#  define __THODD_META_TRAITS_IS_EMPTY_HPP__


namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_empty(
       type_t const&) 
    {
        return
        __is_empty(type_t);
    }
}

#endif