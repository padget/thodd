#ifndef __THODD_CORE_INTEGRAL_HPP__
#  define __THODD_CORE_INTEGRAL_HPP__

#  include <thodd/meta/value.hpp>
#  include <thodd/meta/type.hpp> 
#  include <thodd/core/size_t.hpp>

namespace 
thodd
{
    template<
        typename type_t,
        type_t value_c>
    struct integral_constant:
        meta::type_<integral_constant<type_t, value_c>>,
        meta::value_<type_t, value_c> {};


    template<
        typename type_t,
        type_t _value>
    using igral = integral_constant<type_t, _value>;


    /// Wrapper for bool
    template<bool _b>
    using ibool_ =
        igral<bool, _b>;

    /// Wrapper for short
    template<short _s>
    using ishort_ =
        igral<short, _s>;

    /// Wrapper for unsigned short
    template<unsigned short _us>
    using iushort_ =
        igral<unsigned short, _us>;

    /// Wrapper for char
    template<char _c>
    using ichar_ =
        igral<char, _c>;

    /// Wrapper for char
    template<char _c>
    using iwchar_ =
        igral<wchar_t, _c>;

    /// Wrapper for char
    template<char _c>
    using ichar16_ =
        igral<char16_t, _c>;

    /// Wrapper for char
    template<char _c>
    using ichar32_ =
        igral<char32_t, _c>;

    /// Wrapper for int
    template<int _i>
    using iint_ =
        igral<int, _i>;

    /// Wrapper for long
    template<long _l>
    using ilong_ =
        igral<long, _l>;

    /// Wrapper for long long
    template<long long _ll>
    using ilonglong_ =
        igral<long long, _ll>;

    /// Wrapper for unsigned
    template<unsigned _u>
    using iunsigned_ =
        igral<unsigned, _u>;

    /// Wrapper for unsigned long
    template<unsigned long _ul>
    using iunsignedl_ =
        igral<unsigned long, _ul>;

    /// Wrapper for unsigned long long
    template<unsigned long long _ull>
    using iunsignedll_ =
        igral<unsigned long long, _ull>;

    /// Wrapper for unsigned_t
    template<size_t _s>
    using isize_t_ =
        igral<size_t, _s>;


    using true_ = ibool_<true>;
    using false_ = ibool_<false>;


    constexpr auto iint_0 = iint_<0>{};
    constexpr auto iint_1 = iint_<1>{};
    constexpr auto iint_2 = iint_<2>{};
    constexpr auto iint_3 = iint_<3>{};
    constexpr auto iint_4 = iint_<4>{};
    constexpr auto iint_5 = iint_<5>{};
    constexpr auto iint_6 = iint_<6>{};
    constexpr auto iint_7 = iint_<7>{};
    constexpr auto iint_8 = iint_<8>{};
    constexpr auto iint_9 = iint_<9>{};
    constexpr auto iint_10 = iint_<10>{};
    constexpr auto iint_11 = iint_<11>{};
    constexpr auto iint_12 = iint_<12>{};
    constexpr auto iint_13 = iint_<13>{};
    constexpr auto iint_14 = iint_<14>{};
}

#endif