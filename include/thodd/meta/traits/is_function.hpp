#ifndef __THODD_META_TRAITS_IS_FUNCTION_HPP__
#  define __THODD_META_TRAITS_IS_FUNCTION_HPP__

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    constexpr auto 
    is_function(
        type_<type_t> const&)
    {
        return false;
    }

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...)> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...)&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...)&&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......)> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......)&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......)&&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...) const> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...) const&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...) const&&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......) const> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......) const&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......) const&&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...) volatile> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto
    is_function(
        type_<res_t(args_t...) volatile&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...) volatile&&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......) volatile> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......) volatile&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......) volatile &&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...) const volatile> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...) const volatile&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t...) const volatile&&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......) const volatile> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......) const volatile&> const&)
    {
        return true;
    }
           

    template<
        typename res_t,
        typename ... args_t>
    constexpr auto 
    is_function(
        type_<res_t(args_t......) const volatile &&> const&)
    {
        return true;
    }


    template<
        typename type_t>
    using is_function_t = __type<decltype(is_function(type_<type_t>{}))>;      
}

#endif