#ifndef __THODD_LANG_SOME_HPP__
#  define __THODD_LANG_SOME_HPP__

#  include <thodd/tuple.hpp>
#  include <thodd/law.hpp>
#  include <thodd/variant.hpp>
#  include <thodd/containers.hpp>

#  include <thodd/lang_core.hpp>
#  include <thodd/lang_matcher.hpp>
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
                   max{10u};

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
            matcher<some<matcher<something_t>>> const& __some, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __cpt = 0u;

            while(matches(__some.algo.something, __cursor, __end))
                ++__cpt;

            return __some.algo.min <= __cpt 
                && __cpt <= __some.algo.max;
        }


        template<
            typename something_t>
        inline auto 
        matches(
            word<some<word<something_t>>> const& __some, 
            auto& __cursor, 
            auto const& __end)
        {     
            using token_t = decltype(token(__some, __cursor, __cursor));

            list<token_t> __subranges;

            auto __save = __cursor;            
            auto __cpt = 0u;
            token_t __subrange;
            
            while((__subrange = matches(__some.algo.something, __cursor, __end)) 
                && __cpt <= __some.algo.max)
            {
                std::cout << "addrs : " << &__some.algo.something << std::endl;
                thodd::push_back(__subranges, __subrange);
                ++__cpt;
            }

            if(!(__some.algo.min <= __cpt 
                && __cpt <= __some.algo.max))
            {    
                __subranges.clear();
                __cursor = __save;
            }
            
            std::cout << "addr : " << &__some << std::endl;
            std::cout << sizeof(__some) << std::endl;

            return token(__some, __save, __cursor, __subranges);
        }


        template<
            typename rcase_t>
        constexpr auto
        operator ~ (
            matcher<rcase_t> const& __rmatcher )
        {
            return 
            make_matcher(
                make_some( 
                    __rmatcher));   
        }


        template<
            typename rcase_t>
        constexpr auto
        operator ~ (
            word<rcase_t> const& __rword)
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
            matcher<rcase_t> const& __rmatcher )
        {
            return 
            make_matcher(
                make_some( 
                    __rmatcher))(1, thodd::infinity);   
        }


        template<
            typename rcase_t>
        constexpr auto
        operator + (
            word<rcase_t> const& __rword)
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
            matcher<rcase_t> const& __rmatcher )
        {
            return 
            make_matcher(
                make_some( 
                    __rmatcher))(0, thodd::infinity);   
        }


        template<
            typename rcase_t>
        constexpr auto
        operator * (
            word<rcase_t> const& __rword)
        {
            return 
            make_word(
                make_some( 
                    __rword))(0, thodd::infinity);   
        }
    }
}

#endif 