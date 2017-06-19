#ifndef __THODD_LANG_REGEX_REGEX_HPP__
#  define __THODD_LANG_REGEX_REGEX_HPP__

#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/meta/type.hpp>
#  include <thodd/meta/traits/is_base_of.hpp>
#  include <thodd/meta/traits/require.hpp>

namespace 
thodd::lang::regex
{
    struct regex {} ;


    template<
        typename type_t>
    concept bool regex_based = 
        is_base_of (
            meta::type_<regex>{}, 
            meta::type_<meta::decay_t<type_t>>{}) ;
}

#endif