#ifndef __THODD_LANG_WORD_HPP__
#  define __THODD_LANG_WORD_HPP__

#  include <thodd/functional.hpp>

#  include <thodd/lang_core.hpp>
#  include <thodd/lang_regex.hpp>

namespace thodd
{
    namespace lang
    {

        THODD_EXCEPTION(
            bad_caster_exception, 
            "bad_caster_exception : "
            "the caster is not adapted " 
            "to the found range of stream")

        template<
            typename algo_t, 
            typename caster_t = thodd::id>
        struct word
        {
            algo_t algo;
            caster_t caster;


            constexpr auto
            operator() (
                auto&&... __params) const 
            -> decltype(auto)
            {
                return 
                word
                { algo(perfect<decltype(__params)>(__params)...), caster };
            }


            constexpr auto
            operator[](
                auto&& __caster) const
            -> decltype(auto)
            {
                using ocaster_t = meta::decay<decltype(__caster)>;

                return 
                word<algo_t, ocaster_t>
                { algo, perfect<decltype(__caster)>(__caster) };
            }
        };

        constexpr auto 
        make_word(
            auto&& __algo)
        {
            using algo_t = decltype(__algo);

            return 
            word<meta::decay<algo_t>>
            { perfect<algo_t>(__algo) };
        }


        template<
            typename algo_t, 
            typename caster_t>
        inline auto 
        matches(
            word<regex<algo_t>, caster_t> const& __word, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __save = __cursor;

            if(!(matches(__word.algo, __cursor, __end)))
                __cursor = __save;
                
            return make_token(__save, __cursor);
        }


        template<
            typename ... params_t>
        inline auto 
        matches(
            word<params_t...> const& __word, 
            auto& __cursor, 
            auto const& __end)
        {
            return 
            matches(__word.algo, __cursor, __end);
        }


        template<
            typename algo_t, 
            typename caster_t>
        inline auto 
        interpret(
            word<regex<algo_t>, caster_t> const& __word,
            auto const& __tree)
        {
            if(static_cast<bool>(__tree))
                return __word.caster(__tree);
            else 
                throw bad_caster_exception();
        }
    }
}

#endif