#ifndef __THODD_META_TRAITS_IS_FUNCTION_HPP__
#  define __THODD_META_TRAITS_IS_FUNCTION_HPP__

#  include <thodd/meta/type.hpp>

namespace 
thodd::meta
{
    template<
        typename type_t>
    struct is_function:
            false_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...)>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...)&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...)&&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......)>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......)&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......)&&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...) const>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...) const&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...) const&&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......) const>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......) const&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......) const&&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...) volatile>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...) volatile&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...) volatile&&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......) volatile>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......) volatile&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......) volatile &&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...) const volatile>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...) const volatile&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t...) const volatile&&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......) const volatile>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......) const volatile&>:
            true_ {};

    template<
        typename res_t,
        typename ... args_t>
    struct is_function<res_t(args_t......) const volatile &&>:
            true_ {};
}

#endif