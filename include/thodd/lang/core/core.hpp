#ifndef __THODD_LANG_CORE_HPP__
#  define __THODD_LANG_CORE_HPP__

#  include <thodd/core/perfect.hpp>
#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/container/range.hpp>
#  include <thodd/functional/functional.hpp>

namespace 
thodd::lang
{
    /// Basic token with
    /// no special information
    template<
        typename iterator_t>
    struct basic_token
    {
        using range_t = thodd::detail::range<iterator_t>;

        range_t range;

        constexpr 
        operator bool() const
        {
            return range.begin() != range.end();
        }
    

        inline auto const
        begin() const
        {
            return range.begin();
        }


        inline auto
        begin()
        {
            return range.begin();
        }


        inline auto const
        end() const
        {
            return range.end();
        }


        inline auto
        end()
        {
            return range.end();
        }
    };


    /// Make a basic token
    constexpr auto
    make_token(
        auto&& __begin,
        auto&& __end)
    {
        using iterator_t = meta::decay_t<decltype(__begin)>;

        return
        basic_token<iterator_t>
        { thodd::range(perfect<decltype(__begin)>(__begin),
                        perfect<decltype(__end)>(__end)) };
    }


    extern constexpr auto interpret_ = 
        [] (auto&& __case_getter, 
            auto&& __token_getter)
        {
            return 
            as_functor(
                [&] (auto&& ... __args)
                {
                    return 
                    interpret(
                        __case_getter(perfect<decltype(__args)>(__args)...), 
                        __token_getter(perfect<decltype(__args)>(__args)...));
                });
        };
}

#endif