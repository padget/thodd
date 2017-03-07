#ifndef __THODD_META_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP__
#  define __THODD_META_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP__

namespace 
thodd::meta
{
    constexpr auto 
    is_member_function_pointer(
        auto&&)
    {
        return false;
    }

    template<
        typename type_t, 
        typename class_t>
    constexpr auto 
    is_member_function_pointer(
        type_t class_t::* __t) 
    {
        return 
        is_function(__t);
    }
}

#endif