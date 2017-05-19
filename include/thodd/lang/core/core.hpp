#ifndef __THODD_LANG_CORE_HPP__
#  define __THODD_LANG_CORE_HPP__

#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/core/destroy.hpp>
#  include <thodd/core/begin.hpp>
#  include <thodd/core/end.hpp>

#  include <thodd/meta/traits/decay.hpp>

#  include <thodd/container/range.hpp>
#  include <thodd/container/list.hpp>

#  include <thodd/functional/functional.hpp>

namespace 
thodd::lang
{
    template<
        typename iterator_t>
    class token;

    template<
        typename enum_t>
    struct token
    {
        enum_t type;
    };
}

#endif