#ifndef __THODD_LANG_CORE_TOKEN_HPP__
#  define __THODD_LANG_CORE_TOKEN_HPP__

#  include <thodd/container/range.hpp>
#  include <thodd/pointer/unique.hpp>
#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::lang 
{
    template<
        typename enum_t, 
        typename iterator_t>
    struct token
    {
        enum_t type;
        range<iterator_t> matched;
        unique<token> next;
    };

    constexpr auto 
    make_token(
        auto&& __type, 
        auto&& __begin, 
        auto&& __end)
    {
        using type_t = decltype(__type); 
        using begin_t = decltype(__begin);
        using end_t = decltype(__end);

        return 
        token<
            meta::decay_t<type_t>, 
            meta::decay_t<begin_t>>
        { perfect<type_t>(__type), 
          range<meta::decay_t<begin_t>>
          { perfect<begin_t>(__begin), 
            prefect<end_t>(__end) } };
    }
}

#endif