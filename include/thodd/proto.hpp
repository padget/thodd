#ifndef __THODD_PROTO_HPP__
#  define __THODD_PROTO_HPP__

#  include<thodd/meta.hpp>
#  include<thodd/tuple.hpp> 
#  include<thodd/core/dsl.hpp>
#  include<string>



namespace thodd
{
    namespace testdsl
    {
        namespace detail
        {
            template<
                typename func_t>
            struct test_node
            {
                func_t func;
            };

            template<
                typename params_t>
            struct with_node
            {
                params_t params;                
            };

            template<
                typename assertion_t>
            struct assert_node
            {
                assertion_t assertion;
            };
        }

        template<
            typename func_t>
        constexpr auto
        test(
            func_t&& __func)
        {
            return make_node<detail::test_node>(perfect<func_t>(__func));
        }

        template<
            typename ... params_t>
        constexpr auto
        with(
            params_t&&... __params)
        {
            return  make_node<detail::with_node>(make_tuple(perfect<params_t>(__params)...));
        }

        template<
            typename assertion_t>
        constexpr auto
        assert(
            assertion_t&& __assertion)
        {
            return  make_node<detail::assert_node>(perfect<assertion_t>(__assertion));
        }

        template<
            typename dsl_t>
        struct unit_test;

        
        class test_failed_exception :                                                    
            public std::exception                                       
        {      
            std::string message;

        public:                                                         
            virtual char const* 
            what() const noexcept
            {
                return "test_failed_exception : "; 
            }  
        }; 

        template<
            typename func_t,  
            typename assertion_t, 
            typename ... params_t>
        using test_with_assert = 
                dsl_expression<
                    detail::test_node<func_t>, 
                    detail::with_node<params_t...>,
                    detail::assert_node<assertion_t>>;

        template<
            typename func_t,  
            typename assertion_t,
            typename ... params_t>
        struct unit_test<
                test_with_assert<
                    func_t, 
                    assertion_t, 
                    params_t...>>
        {
            template<
                typename ... args_t>
            inline void
            operator()(
                test_with_assert<
                    func_t,  
                    assertion_t, 
                    params_t...> const& __cdsl,
                args_t&&... __args) const
            {
                (*this)(make_indexes<sizeof...(params_t)>{}, 
                        __cdsl, 
                        perfect<args_t>(__args)...);
            }

            template<
                typename ... args_t, 
                size_t ... indexes_c>
            inline void
            operator()(
                indexes<indexes_c...> const&,
                test_with_assert<
                    func_t,  
                    assertion_t, 
                    params_t...> const& __cdsl,
                args_t&&... __args) const
            {
                auto&& __func = get<0>(__cdsl).func(
                                    perfect<args_t>(__args)...);
                auto&& __params = get<1>(__cdsl).params;
                auto&& __assertion = get<2>(__cdsl).assertion;

                if(!__assertion(
                        __func(get<indexes_c>(__params)(
                            perfect<args_t>(__args)...)...), 
                        perfect<args_t>(__args)...))
                     throw test_failed_exception();
            }
        };
    }
}

#endif