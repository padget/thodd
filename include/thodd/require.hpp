/*
 * require.hpp
 *
 *  Created on: 11 août 2016
 *      Author: padget
 */

#ifndef THODD_REQUIRE_HPP_
#  define THODD_REQUIRE_HPP_

#  include <thodd/law.hpp>
#  include <thodd/dsl.hpp>

namespace thodd
{
    namespace detail
    {
        template<
            typename cond_t>
        struct require_node
        {
            cond_t cond;
        };

        template<
            typename exception_t>
        struct throw_node
        {
            using exception = exception_t;
        };

        template<
            typename func_t>
        struct to_node
        {
            func_t func;
        };
    }

    template<
        typename cond_t>
    constexpr auto
    require(
        cond_t&& __cond)
    {
        return node<detail::require_node>(perfect<cond_t>(__cond));
    }

    template<
        typename exception_t>
    constexpr auto
    throw_()
    {
        return dsl_node<detail::throw_node<exception_t>>{};
    }

    template<
        typename func_t>
    constexpr auto
    to(
        func_t&& __func)
    {
        return node<detail::to_node>(perfect<func_t>(__func));
    }




    template<
        typename dsl_t>
    struct contract;

    template<
        typename cond_t, 
        typename exception_t>
    using require_throw = 
            dsl_expression<
                detail::require_node<cond_t>, 
                detail::throw_node<exception_t>>;

    template<
        typename cond_t, 
        typename exception_t>
    struct contract<
            require_throw<
                cond_t, 
                exception_t>>
    {
        template<
            typename ... args_t>
        inline auto
        operator() (
            require_throw<cond_t, exception_t> const& __dsl,
            args_t&&... __args) const
        {
            auto&& __cond = get<0>(__dsl).cond;
            
            if(!__cond(perfect<args_t>(__args)...))
                throw exception_t{};
        }
    };

    template<
        typename cond_t, 
        typename func_t>
    using require_to = 
            dsl_expression<
                detail::require_node<cond_t>, 
                detail::to_node<func_t>>;

    template<
        typename cond_t, 
        typename func_t>
    struct contract<
            require_to<
                cond_t, 
                func_t>>
    {
        template<
            typename ... args_t>
        inline auto
        operator() (
            require_to<cond_t, func_t> const& __dsl,
            args_t&&... __args) const
        {
            auto&& __cond = get<0>(__dsl).cond;
            auto&& __func = get<1>(__dsl).func;

            if(__cond(perfect<args_t>(__args)...))
                __func(perfect<args_t>(__args)...);
        }
    };
}


#endif /* THODD_REQUIRE_HPP_ */
