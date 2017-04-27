#ifndef __THODD_LANG_ALTERNATIVE_ALTERNATIVE_TOKEN_HPP__
#  define __THODD_LANG_ALTERNATIVE_ALTERNATIVE_TOKEN_HPP__

#  include <thodd/container/range.hpp>

//#  include <thodd/variant/variant.hpp>
#  include <thodd/tuple/dynamic_tuple.hpp>

#  include <thodd/core/size_t.hpp>
#  include <thodd/core/between.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/perfect.hpp>

#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::lang
{
    template<
        typename iterator_t, 
        typename ... subtokens_t>
    struct alternative_token
    {
        using range_t = thodd::detail::range<iterator_t>;

        range_t range;
        dynamic_tuple<subtokens_t...> subranges;
        size_t index;


        constexpr
        operator bool () const
        {
            return 
            true;
        }


        inline auto const
        begin() const
        {
            return 
            range.begin();
        }


        inline auto
        begin()
        {
            return 
            range.begin();
        }


        inline auto const
        end() const
        {
            return 
            range.end();
        }


        inline auto
        end()
        {
            return 
            range.end();
        }
    };


    template<
        typename ... subtokens_t>
    constexpr auto
    make_alternative_token(
        auto&& __begin, 
        auto&& __end, 
        dynamic_tuple<subtokens_t...> const& __subranges, 
        auto&& __index)
    {
        using iterator_t = meta::decay_t<decltype(__begin)>;

        return 
        alternative_token<iterator_t, subtokens_t...>
        { thodd::range(
            perfect<decltype(__begin)>(__begin),
            perfect<decltype(__end)>(__end)),
            __subranges, 
            perfect<decltype(__index)>(__index) };
    }


    template<
        typename ... subtokens_t>
    constexpr auto
    make_alternative_token(
        auto&& __begin, 
        auto&& __end, 
        dynamic_tuple<subtokens_t...>&& __subranges, 
        auto&& __index)
    {
        using iterator_t = meta::decay_t<decltype(__begin)>;

        return 
        alternative_token<iterator_t, subtokens_t...>
        { thodd::range(
            perfect<decltype(__begin)>(__begin),
            perfect<decltype(__end)>(__end)),
            thodd::rvalue(__subranges), 
            perfect<decltype(__index)>(__index) };
    }
}

#endif