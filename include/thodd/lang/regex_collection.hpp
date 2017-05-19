#ifndef __THODD_LANG_REGEX_COLLECTION_HPP__
#  define __THODD_LANG_REGEX_COLLECTION_HPP__

#  include <thodd/lang/core/regex.hpp>
#  include <thodd/functional/functional.hpp>

namespace 
thodd::lang
{
    extern constexpr 
    auto letter = 
        thodd::lang::make_regex(
            tern(val('a') < *$0 && *$0 < val('z'))
                ((++$0, val(true)))
                (val(false)));

    extern constexpr 
    auto digit = 
        thodd::lang::make_regex(
            tern(val('0') < *$0 && *$0 < val('9'))
                ((++$0, val(true)))
                (val(false)));
}

#endif