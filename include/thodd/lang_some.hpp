#ifndef __THODD_LANG_SOME_HPP__
#  define __THODD_LANG_SOME_HPP__

#  include <thodd/tuple.hpp>
#  include <thodd/law.hpp>
#  include <thodd/variant.hpp>
#  include <thodd/containers.hpp>

#  include <thodd/lang_core.hpp>
#  include <thodd/lang_regex.hpp>
#  include <thodd/lang_word.hpp> 

namespace thodd
{
    namespace lang
    {
        template<
            typename something_t>
        struct some
        {
            something_t something;
            size_t min{0u}, 
                   max{thodd::infinity};

            constexpr auto 
            operator() (
                size_t __min, size_t __max) const 
            -> decltype(auto)
            {
                return some{something, __min, __max};
            }
        };

        constexpr auto
        make_some(
            auto&& __something)
        {
            return 
            some<meta::decay<decltype(__something)>>
            {perfect<decltype(__something)>(__something)};
        }


        template<
            typename something_t>
        inline auto
        matches(
            regex<some<regex<something_t>>> const& __some, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __cpt = 0u;

            while(matches(__some.algo.something, __cursor, __end))
                ++__cpt;

            return 
            thodd::between(
                __cpt, 
                __some.algo.min,
                __some.algo.max);
        }


        template<
            typename something_t,
            typename caster_t, 
            typename some_caster_t>
        inline auto 
        matches(
            word<some<word<something_t,  caster_t>>, some_caster_t> const& __some, 
            auto& __cursor, 
            auto const& __end)
        {     
            using token_t = decltype(token(false, 0u, __cursor, __cursor));

            auto __save = __cursor;            
            auto __cpt  = 0u;

            token_t       __subrange;
            list<token_t> __subranges;
            
            while((__subrange = matches(__some.algo.something, __cursor, __end)) 
                && __cpt <= __some.algo.max)
            {
                thodd::push_back(
                    __subranges, 
                    thodd::rvalue(__subrange));
                
                ++__cpt;
            }

            auto&& __valid = 
                thodd::between(
                    __cpt, 
                    __some.algo.min,
                    __some.algo.max);

            std::cout << std::boolalpha << __valid << std::endl;    
            
            if(!__valid)
            {    
                __subranges.clear();
                __cursor = __save;
            }

            return 
            token(
                __valid, 
                0u, 
                __save, 
                __cursor, 
                thodd::rvalue(__subranges));
        }


        template<
            typename something_t, 
            typename caster_t, 
            typename some_caster_t>
        inline auto 
        interpret(
            word<some<word<something_t,  caster_t>>, some_caster_t> const& __some,
            auto&& __tree)
        {
            using item_t = decltype(
                            interpret(
                                __some.algo.something, 
                                *__tree.subranges.begin()));

            list<meta::decay<item_t>> __lst;

            for(auto const& __tk : __tree.subranges)
                thodd::push_back(__lst, thodd::rvalue(interpret(__some.algo.something, __tk)));

            return __some.caster(__lst);
        }


        template<
            typename rcase_t>
        constexpr auto
        operator ~ (
            regex<rcase_t> const& __rregex)
        {
            return 
            make_regex(
                make_some( 
                    __rregex));   
        }


        template<
            typename rcase_t, 
            typename rcaster_t>
        constexpr auto
        operator ~ (
            word<rcase_t, rcaster_t> const& __rword)
        {
            return 
            make_word(
                make_some( 
                    __rword));   
        }

        template<
            typename rcase_t>
        constexpr auto
        operator + (
            regex<rcase_t> const& __rregex)
        {
            return 
            make_regex(
                make_some( 
                    __rregex))(1, thodd::infinity);   
        }


        template<
            typename rcase_t, 
            typename rcaster_t>
        constexpr auto
        operator + (
            word<rcase_t, rcaster_t> const& __rword)
        {
            return 
            make_word(
                make_some( 
                    __rword))(1, thodd::infinity);   
        }

        template<
            typename rcase_t>
        constexpr auto
        operator * (
            regex<rcase_t> const& __rregex)
        {
            return 
            make_regex(
                make_some( 
                    __rregex))(0, thodd::infinity);   
        }


        template<
            typename rcase_t, 
            typename rcaster_t>
        constexpr auto
        operator * (
            word<rcase_t, rcaster_t> const& __rword)
        {
            return 
            make_word(
                make_some( 
                    __rword))(0, thodd::infinity);   
        }
    }
}

#endif 