#ifndef __THODD_LANG_REGEX_REGEX_HPP__
#  define __THODD_LANG_REGEX_REGEX_HPP__

#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/meta/type.hpp>
#  include <thodd/meta/traits/is_base_of.hpp>

namespace 
thodd::lang::regex
{
    struct regex {} ;

    template<
        typename type_t>
    constexpr auto
    is_regex_based(
        type_t&&)
    {
        using namespace thodd::meta;
        
        return 
        is_base_of(
            type_<regex>{}, 
            type_<decay_t<type_t>>{}) ;
    }
}

#endif