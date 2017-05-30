#ifndef __THODD_LANG_REGEX_HPP__
#  define __THODD_LANG_REGEX_HPP__

#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/lang/regex/regex.hpp>

namespace 
thodd::lang::regex
{
    constexpr auto 
    make_regex(
        auto&& __algo)
    {
        return 
        regex<meta::decay_t<decltype(__algo)>>
        { perfect<decltype(__algo)>(__algo) };
    }
}

#endif