#ifndef __THODD_LANG_WORD_HPP__
#  define __THODD_LANG_WORD_HPP__

#  include <thodd/lang_core.hpp>
#  include <thodd/lang_matcher.hpp>

namespace thodd
{
    namespace lang
    {
        template<
            typename algo_t>
        struct word
        {
            algo_t algo;
           

            constexpr auto
            operator() (
                auto&&... __params) const 
            -> decltype(auto)
            {
                return word{algo(perfect<decltype(__params)>(__params)...)};
            }
        };

        constexpr auto 
        make_word(
            auto&& __algo)
        {
            using algo_t = decltype(__algo);

            return 
            word<meta::decay<algo_t>>
            {perfect<algo_t>(__algo)};
        }


        template<
            typename algo_t>
        inline auto 
        matches(
            word<matcher<algo_t>> const& __word, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __save = __cursor;

            if(!matches(__word.algo , __cursor, __end))
                __cursor = __save;
                
            return token(0u, __save, __cursor);
        }


        template<
            typename algo_t>
        inline auto 
        matches(
            word<algo_t> const& __word, 
            auto& __cursor, 
            auto const& __end)
        {
            return matches(__word.algo, __cursor, __end);
        }
    }
}

#endif