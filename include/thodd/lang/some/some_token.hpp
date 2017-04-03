#ifndef __THODD_LANG_SOME_SOME_TOKEN_HPP__
#  define __THODD_LANG_SOME_SOME_TOKEN_HPP__

#  include <thodd/container/range.hpp>
#  include <thodd/container/list.hpp>

#  include <thodd/core/infinity.hpp>
#  include <thodd/core/size_t.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/begin.hpp>
#  include <thodd/core/end.hpp>

#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::lang
{
    template<
        typename iterator_t, 
        typename subtoken_t>
    struct some_token
    {
        using range_t = thodd::detail::range<iterator_t>;

        range_t range;
        thodd::list<subtoken_t> subranges;
        size_t min{0u}; 
        size_t max{thodd::infinity};


        constexpr
        operator bool () const
        {
            return 
            thodd::between(
                subranges.size(), 
                min, max);
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
        typename subtoken_t>
    constexpr auto
    make_some_token(
        auto&& __begin, 
        auto&& __end, 
        thodd::list<subtoken_t> const& __subranges, 
        size_t const& __min, 
        size_t const& __max)
    {
        using iterator_t = meta::decay_t<decltype(__begin)>;

        return 
        some_token<iterator_t, subtoken_t>
        { thodd::range(
            perfect<decltype(__begin)>(__begin),
            perfect<decltype(__end)>(__end)),
            __subranges, 
            __min, 
            __max };
    }


    template<
        typename subtoken_t>
    constexpr auto
    make_some_token(
        auto&& __begin, 
        auto&& __end, 
        thodd::list<subtoken_t>&& __subranges, 
        size_t const& __min, 
        size_t const& __max)
    {
        using iterator_t = meta::decay_t<decltype(__begin)>;

        return 
        some_token<iterator_t, subtoken_t>
        { thodd::range(
            perfect<decltype(__begin)>(__begin),
            perfect<decltype(__end)>(__end)),
            thodd::rvalue(__subranges), 
            __min, 
            __max };
    }
}

#endif 