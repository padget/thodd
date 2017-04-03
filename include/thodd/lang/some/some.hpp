#ifndef __THODD_LANG_SOME_HPP__
#  define __THODD_LANG_SOME_HPP__

#  include <thodd/tuple/tuple.hpp>

#  include <thodd/core/between.hpp>

#  include <thodd/container/list.hpp>

#  include <thodd/lang/core/core.hpp>
#  include <thodd/lang/core/regex.hpp>
#  include <thodd/lang/core/word.hpp> 

namespace 
thodd::lang
{
    template<
        typename something_t>
    struct some
    {
        something_t something;
        size_t min{0u}, 
               max{thodd::infinity};

        constexpr auto 
        operator() (
            size_t __min, size_t __max) const 
        -> decltype(auto)
        {
            return 
            some
            { something, __min, __max };
        }
    };


    constexpr auto
    make_some(
        auto&& __something)
    {
        return 
        some<meta::decay_t<decltype(__something)>>
        { perfect<decltype(__something)>(__something) };
    }


    template<
        typename rcase_t>
    constexpr auto
    operator ~ (
        regex<rcase_t> const& __rregex)
    {
        return 
        make_regex(
            make_some( 
                __rregex));   
    }


    template<
        typename rcase_t, 
        typename rcaster_t>
    constexpr auto
    operator ~ (
        word<rcase_t, rcaster_t> const& __rword)
    {
        return 
        make_word(
            make_some( 
                __rword));   
    }

    template<
        typename rcase_t>
    constexpr auto
    operator + (
        regex<rcase_t> const& __rregex)
    {
        return 
        make_regex(
            make_some( 
                __rregex))(1, thodd::infinity);   
    }


    template<
        typename rcase_t, 
        typename rcaster_t>
    constexpr auto
    operator + (
        word<rcase_t, rcaster_t> const& __rword)
    {
        return 
        make_word(
            make_some( 
                __rword))(1, thodd::infinity);   
    }


    template<
        typename rcase_t>
    constexpr auto
    operator * (
        regex<rcase_t> const& __rregex)
    {
        return 
        make_regex(
            make_some( 
                __rregex))(0, thodd::infinity);   
    }


    template<
        typename rcase_t, 
        typename rcaster_t>
    constexpr auto
    operator * (
        word<rcase_t, rcaster_t> const& __rword)
    {
        return 
        make_word(
            make_some( 
                __rword))(0, thodd::infinity);   
    }
}

#endif 