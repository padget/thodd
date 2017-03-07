#ifndef __THODD_META_TRAITS_IS_CLASS_HPP__
#  define __THODD_META_TRAITS_IS_CLASS_HPP__


namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto
    is_class(
       type_t const&) 
    {
        return
        __is_class(type_t);
    }
}

#endif