#ifndef __THODD_LANG_FOLLOW_FOLLOW_TOKEN_HPP__
#  define __THODD_LANG_FOLLOW_FOLLOW_TOKEN_HPP__

#  include <thodd/core/begin.hpp>
#  include <thodd/core/end.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/perfect.hpp>

#  include <thodd/functional/functional.hpp>

#  include <thodd/tuple/dynamic_tuple.hpp>

#  include <thodd/container/range.hpp>
#  include <thodd/container/functional.hpp>

#  include <thodd/meta/traits/decay.hpp>

namespace
thodd::lang
{
    template<
        typename iterator_t, 
        typename ... subtokens_t>
    struct follow_token
    {
        using range_t = thodd::detail::range<iterator_t>;

        range_t range;
        thodd::dynamic_tuple<subtokens_t...> subranges;

        constexpr
        operator bool () const
        {
            auto __res = true;

            thodd::foreach(
                subranges, 
                thodd::ref(__res) = 
                    thodd::cref(__res) 
                    && ($0 != val(nullptr)));

            if(__res)
                thodd::foreach(
                    subranges,
                    thodd::ref(__res) = 
                        thodd::cref(__res) 
                        && thodd::bind(thodd::cast_<bool>, *$0));

            return __res; 
        }

        inline auto const
        begin() const
        {
            return 
            thodd::begin(range);
        }


        inline auto
        begin()
        {
            return 
            thodd::begin(range);
        }


        inline auto const
        end() const
        {
            return 
            thodd::end(range);
        }


        inline auto
        end()
        {
            return 
            thodd::end(range);
        }


        inline auto const
        subbegin() const
        {
            return 
            thodd::begin(subranges);
        }


        inline auto
        subbegin()
        {
            return 
            thodd::begin(subranges);
        }


        inline auto const
        subend() const
        {
            return 
            thodd::end(subranges);
        }


        inline auto
        subend()
        {
            return 
            thodd::end(subranges);
        }
    };

    template<
        typename ... subtokens_t>
    constexpr auto 
    make_follow_token(
        auto&& __begin, 
        auto&& __end,
        thodd::dynamic_tuple<subtokens_t...>&& __subranges)
    {
        return 
        follow_token<
            meta::decay_t<decltype(__begin)>, 
            subtokens_t...>
        { { decltype(__begin)(__begin), 
            decltype(__end)(__end) }, 
          thodd::rvalue(__subranges) };
    }
}

#endif