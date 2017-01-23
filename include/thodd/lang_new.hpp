#ifndef __THODD_LANG2_HPP__
#  define __THODD_LANG2_HPP__

#  include <limits>

#  include <thodd/tuple.hpp> 
#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/variant.hpp>
#  include <thodd/containers.hpp>

namespace thodd
{
    namespace lang
    {
        template<
            typename caster_t>
        using __target = typename caster_t::target;


        inline auto
        attribute(
            auto&& __caster)
        -> decltype(auto)
        {
            using target_t = __target<meta::decay<decltype(__caster)>>;

            return target_t{};
        }

        inline auto 
        matches(
            auto&& __matcher, 
            auto& __cursor, 
            auto const& __end)
        {
            return __matcher(__cursor, __end);
        }


        template<
            typename matcher_t, 
            typename caster_t>
        struct parser
        {
            matcher_t match;
            caster_t cast;

            using target = __target<caster_t>;

            inline auto 
            operator()(
                auto& __cursor, 
                auto const& __end) const
            {
                return matches(match, __cursor, __end);
            }

            
            inline auto
            operator()(
                auto& __cursor, 
                auto& __end, 
                auto& __tgt) const
            {
                auto __save = __cursor;
                
                if(matches(__cursor, __end))
                {   
                    cast(__save, __cursor, __tgt);
                    return true;
                }
                
                __cursor = __save;
                return false;
            }
        };

        
        template<
            typename ... params_t>
        inline auto 
        matches(
            parser<params_t...> const& __parser, 
            auto& __cursor, 
            auto const& __end)
        {
            return __parser(__cursor, __end);
        }



        template<
            typename ... cases_t>
        struct alternative
        {
            tuple<cases_t...> cases;

            using target = variant<__target<cases_t>...>;
        };


        template<
            typename ... cases_t>
        inline auto 
        matches(
            alternative<cases_t...> const& __alter, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __res = false;                
            auto __save = __cursor;

            __alter.cases.template foreach(
                [&__res, &__save, &__cursor, &__end] (auto&& __case)
                {
                    if(!__res) 
                        __res |= perfect<decltype(__case)>(__case)(__cursor, __end);  
                    
                    if(!__res) 
                        __cursor = __save;

                    return __res;
                });
        
            return __res;
        }


        template<
            typename something_t>
        struct some
        {
            something_t something;
            size_t min{0u}, 
                   max{1u};

            using target = list<__target<something_t>>;

            constexpr some<something_t>
            operator()(
                size_t __min, 
                size_t __max) const
            {
                return {something, __min, __max};
            }
        };


        inline auto
        matches(
            some<auto> const& __some, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __cpt = 0u;

            while(__some.something(__cursor, __end))
                ++__cpt;

            return __some.min <= __cpt 
                && __cpt <= __some.max;
        }


        template<
            typename ... algos_t>
        struct follow
        {
            tuple<algos_t...> algos;

            using target = tuple<__target<algos_t>...>;
        };


        template<
            typename ... algos_t>
        inline auto 
        matches(
            follow<algos_t...> const& __follow, 
            auto& __cursor, 
            auto const& __end)
        {
            auto __res = true;
            auto __save = __cursor;

            __follow.algos.template foreach(
                [&__res, &__save, &__cursor, &__end] (auto&& __algo)
                {
                    if(__res) 
                        __res &= perfect<decltype(__algo)>(__algo)
                                    (__cursor, __end);

                    return __res;
                });

            if(!__res)
                __cursor = __save;
            
            return __res;
        } 
    }
}

#endif // !__THODD_LANG2_HPP__