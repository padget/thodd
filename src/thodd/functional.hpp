/*
 * functional.hpp
 *
 *  Created on: 13 sept. 2016
 *      Author: Benjamin
 */
 
#ifndef ATOM_FUNCTIONAL_HPP_
#  define ATOM_FUNCTIONAL_HPP_

#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>
#  include <thodd/tuple.hpp>
#  include <iostream>

namespace thodd
{
	/// Statements
    template<
        typename left_t,
        typename right_t>
    struct statements
    {
        meta::remove_all<left_t> left;
        meta::remove_all<right_t> right;

        template<
            typename ... args_t>
        constexpr decltype(auto)
        operator () (
            args_t&&... _args) const
        {
            left(perfect<decltype(_args)>(_args)...);
            return right(perfect<decltype(_args)>(_args)...);
        }
    };





    template<
        typename base_t>
    struct functor;


    /// Convert an instance
    /// of base_t into an actor
    /// The only requirement is
    /// that base_t class has
    /// the ()(args_t&&...) method
    template<
        typename base_t>
    constexpr functor<base_t>
    as_functor(
        base_t&& _base)
    {
        return {perfect<base_t>(_base)};
    }


    /// An functor is an object
    /// that can be considered
    /// as inline function object.
    /// It has an base of base_t
    /// and calls the () method
    /// on this instance of base_t
    template<
        typename base_t>
    struct functor
    {
        meta::remove_all<base_t> base;

        /// Main function of an
        /// actor. It takes some
        /// arguments and call the
        /// method eval of the
        /// base object
        template<
            typename ... args_t>
        constexpr decltype(auto)
        operator()(
            args_t&&... _args) const
        {
            return base(perfect<args_t>(_args)...);
        }


        template<
            typename obase_t>
        struct assignement
        {
            functor<base_t> this_;
            functor<obase_t> other;

            template<
                typename ... args_t>
            constexpr decltype(auto)
            operator()(
                args_t&&... _args) const
            {
                return this_(perfect<args_t>(_args)...) = other(perfect<args_t>(_args)...);
            }
        };

        template<
            typename obase_t>
        constexpr auto
        operator=(
            functor<obase_t> const& _other) const
        {
            return as_functor(assignement<obase_t>{*this, _other});
        }

        template<
            typename obase_t>
        constexpr auto
        operator=(
            functor<obase_t> && _other) const
        {
            return as_functor(assignement<obase_t>{*this, _other});
        }
    };


    template<
        typename base_t,
        typename base2_t>
    constexpr auto
    operator , (
        functor<base_t> const& _functor,
        functor<base2_t> const& _functor2)
    {
        return as_functor(statements<base_t, base2_t>{_functor.base, _functor2.base});
    }

    template<
        typename base_t,
        typename base2_t>
    constexpr auto
    operator , (
        functor<base_t> const& _functor,
        functor<base2_t> && _functor2)
    {
        return as_functor(statements<base_t, base2_t>{_functor.base, _functor2.base});
    }

    template<
        typename base_t,
        typename base2_t>
    constexpr auto
    operator , (
        functor<base_t> && _functor,
        functor<base2_t> const& _functor2)
    {
        return as_functor(statements<base_t, base2_t>{_functor.base, _functor2.base});
    }

    template<
        typename base_t,
        typename base2_t>
    constexpr auto
    operator , (
        functor<base_t> && _functor,
        functor<base2_t> && _functor2)
    {
        return as_functor(statements<base_t, base2_t>{_functor.base, _functor2.base});
    }



    namespace detail
    {
        struct nothing
        {
            template<
                typename ... args_t>
            constexpr void
            operator()(
                args_t&&...) const {}
        };
    }

    extern constexpr auto nothing = as_functor(detail::nothing{});



    namespace detail
    {
        struct compose_builder
        {
            template<
                typename func1_t,
                typename func2_t>
            struct compose_impl
            {
                meta::remove_all<func1_t> func1;
                meta::remove_all<func2_t> func2;

                template<
                    typename ... args_t>
                constexpr decltype(auto)
                operator()(
                    args_t&&... _args) const
                {
                    return func1(func2(perfect<args_t>(_args)...));
                }
            };

            template<
                typename func1_t,
                typename func2_t>
            constexpr auto
            operator() (
                func1_t&& _func1,
                func2_t&& _func2) const
            {
                return as_functor(compose_impl<func1_t, func2_t>{
                            perfect<func1_t>(_func1),
                            perfect<func2_t>(_func2)});
            }
        };
    }

    extern constexpr auto compose = detail::compose_builder{};




    namespace detail
    {
        struct demux_builder
        {
            template<
                typename indexes_t,
                typename func_t,
                typename ... funcs_t>
            struct demux_impl;

            template<
                size_t... indexes_c,
                typename func_t,
                typename ... funcs_t>
            struct demux_impl<indexes<indexes_c...>, func_t, funcs_t...>
            {
                meta::remove_all<func_t> func;

                tuple<meta::remove_all<funcs_t>...> funcs;

                template<
                    typename ... args_t>
                constexpr decltype(auto)
                operator()(
                    args_t&&... _args) const
                {
                    return func(get<indexes_c>(funcs)(perfect<args_t>(_args)...)...);
                }
            };

            template<
                typename func_t,
                typename ... funcs_t>
            constexpr auto
            operator()(
                func_t&& _func,
                funcs_t&&... _funcs) const
            {
                return as_functor(demux_impl<make_indexes<sizeof...(funcs_t)>, func_t, funcs_t...>{
                        perfect<func_t>(_func),
                        make_tuple(perfect<funcs_t>(_funcs)...)});
            }
        };
    }

    extern constexpr auto demux = as_functor(detail::demux_builder{});
    extern constexpr auto bind = demux;



    /*namespace detail
	{
    	struct member_builder
    	{
    		template<
				typename func_t,
				typename instance_t,
				typename ... bindeds_t>
    		struct member_impl
			{
    			meta::decay<func_t> func;
    			instance_t&& instance;
    			tuple<meta::decay<bindeds_t>...> bindeds;

    			template<
					typename ... args_t>
    			constexpr decltype(auto)
    			operator()(
					args_t&&... _args) const
    			{
    				return bindeds.functional_apply(instance.*func, perfect<args_t>(_args)...);
    			}
			};

    		template<
				typename func_t,
				typename instance_t,
				typename ... bindeds_t>
    		constexpr member_impl<func_t, instance_t, bindeds_t...>
    		operator()(
    			func_t&& _func,
				instance_t&& _instance,
				bindeds_t&&... _bindeds) const
    		{
    			return {perfect<func_t>(_func),
    					perfect<instance_t>(_instance),
						make_tuple(perfect<bindeds_t>(_bindeds)...)};
    		}
    	};
	}


    constexpr detail::member_builder member;

*/

    extern constexpr auto
	member = as_functor([](auto&& _func,
						   auto&& _instance,
						   auto&&... _prebinded)
						   {
							  return as_functor(
									  [&](auto&&... _args)
										->decltype(auto)
										{
											using func_t = decltype(_func);
											using instance_t = decltype(_instance);

											return (perfect<instance_t>(_instance).*perfect<func_t>(_func))(_prebinded(perfect<decltype(_args)>(_args)...)...);
										});
						   });

    namespace detail
    {
        struct for_impl
        {
            template<
                typename init_t,
                typename cond_t,
                typename step_t>
            struct for_init_cond_step_impl
            {
                meta::remove_all<init_t> init;
                meta::remove_all<cond_t> cond;
                meta::remove_all<step_t> step;


                template<
                    typename then_t>
                struct for_init_cond_step_then_impl
                {
                    meta::remove_all<init_t> init;
                    meta::remove_all<cond_t> cond;
                    meta::remove_all<step_t> step;
                    meta::remove_all<then_t> then;

                    template<
                        typename ... args_t>
                    constexpr void
                    operator()(
                        args_t&&... _args) const
                    {
                        for(init(perfect<args_t>(_args)...);
                            cond(perfect<args_t>(_args)...);
                            step(perfect<args_t>(_args)...))
                            then(perfect<args_t>(_args)...);
                    }
                };

                template<
                    typename then_t>
                constexpr decltype(auto)
                operator()(
                    then_t&& _then) const
                {
                    return for_init_cond_step_then_impl<then_t>{init, cond, step, perfect<then_t>(_then)};
                }

            };

            template<
                typename init_t,
                typename cond_t,
                typename step_t>
            constexpr decltype(auto)
            operator()(
                init_t&& _init,
                cond_t&& _cond,
                step_t&& _step) const
            {
                return for_init_cond_step_impl<init_t, cond_t, step_t>{
                    perfect<init_t>(_init),
                    perfect<cond_t>(_cond),
                    perfect<step_t>(_step)};
            }
        };
    }

    extern constexpr auto for_ = as_functor(detail::for_impl{});




    namespace detail
    {
        struct if_impl
        {
            template<
                typename cond_t>
            struct if_cond_impl
            {
                meta::remove_all<cond_t> cond;

                template<
                    typename then_t>
                struct if_cond_then_impl
                {
                    meta::remove_all<cond_t> cond;
                    meta::remove_all<then_t> then;

                    template<
                        typename ... args_t>
                    constexpr decltype(auto)
                    operator()(
                        args_t&&... _args) const
                    {
                        if(cond(perfect<args_t>(_args)...))
                            return then(perfect<args_t>(_args)...);
                    }

                    template<
                        typename else_then_t>
                    struct if_cond_then_else_else_then_impl
                    {
                        meta::remove_all<cond_t> cond;
                        meta::remove_all<then_t> then;
                        meta::remove_all<else_then_t> else_then;

                        template<
                            typename ... args_t>
                        constexpr decltype(auto)
                        operator()(
                            args_t&&... _args) const
                        {
                            if(cond(perfect<args_t>(_args)...))
                                return then(perfect<args_t>(_args)...);
                            else
                                return else_then(perfect<args_t>(_args)...);
                        }
                    };

                    template<
                        typename else_then_t>
                    constexpr decltype(auto)
                    else_(
                        else_then_t&& _else_then) const
                    {
                        return if_cond_then_else_else_then_impl<else_then_t>{cond, then, perfect<else_then_t>(_else_then)};
                    }

                };

                template<
                    typename then_t>
                constexpr decltype(auto)
                operator()(
                    then_t&& _then) const
                {
                    return if_cond_then_impl<then_t>{cond, perfect<then_t>(_then)};
                }
            };


            template<
                typename cond_t>
            constexpr decltype(auto)
            operator()(
                cond_t&& _cond) const
            {
                return if_cond_impl<cond_t>{perfect<cond_t>(_cond)};
            }
        };
    }


    extern constexpr auto
    if_ = as_functor(detail::if_impl{});

/*

    namespace detail
    {
        struct iterate_impl
        {
            template<
                size_t iteration_c,
                typename func_t>
            struct iteration_step_impl
            {
                meta::remove_all<func_t> func;



                template<
                    typename ... args_t>
                constexpr decltype(auto)
                operator()(
                    args_t&& ... _args) const
                {
                    static_assert(iteration_c > 0,
                        "template <size_t iteration_c, "
                        "typename func_t> iteration_step_impl : "
                        "the number of iteration must be > 0");

                    constexpr auto&& static_if = compile::if_;
                    return static_if(ibool_<(iteration_c >= 2)>{})
                                  (compose(func, iteration_step_impl<iteration_c - 1, func_t>{func}))
                           .else_
                                  (static_if(ibool_<(iteration_c == 1)>{})
                                    (func))
                           (perfect<args_t>(_args)...);
                }

            };

            template<
                typename nb_iteration_t,
                nb_iteration_t nb_iteration_c,
                typename func_t>
            constexpr auto
            operator()(
                igral<nb_iteration_t, nb_iteration_c> const&,
                func_t&& _func) const
            {
                return as_functor(iteration_step_impl<nb_iteration_c, func_t>{_func});
            }
        };
    }

    constexpr auto iterate = as_functor(detail::iterate_impl{});

*/


    namespace detail
    {
        /// Encapsulate a
        /// lvalue &
        template<
            typename ref_t>
        struct reference
        {
            ref_t& ref;


            template<
                typename ... args_t>
            constexpr ref_t&
            operator()(
                args_t&&... _args) const
            {
                return ref;
            }
        };

        /// Encapsulate a
        /// const lvalue &
        template<
            typename ref_t>
        struct const_reference
        {
            ref_t const& ref;


            template<
                typename ... args_t>
            constexpr ref_t const&
            operator()(
                args_t&&... _args) const
            {
                return ref;
            }
        };

        /// Encapsulate a
        /// value and rvalue
        template<
            typename value_t>
        struct value
        {
            value_t m_ref;

            template<
                typename ... args_t>
            constexpr value_t const&
            operator()(
                args_t&&... _args) const
            {
                return m_ref;
            }
        };
    }


    /// Return an actor
    /// based on reference
    template<
        typename type_t>
    constexpr functor<detail::reference<type_t>>
    ref(
        type_t& _ref)
    {
        return {_ref};
    }


    /// Return an actor
    /// based on const_reference
    template<
        typename type_t>
    constexpr functor<detail::const_reference<type_t>>
    cref(
        type_t&& _ref)
    {
        return {perfect<type_t>(_ref)};
    }


    /// Return an actor
    /// based on value
    template<
        typename type_t>
    constexpr functor<detail::value<meta::decay<type_t>>>
    val(
        type_t&& _ref)
    {
        return {perfect<type_t>(_ref)};
    }




    namespace detail
    {
        struct on_impl
        {
            template<
                typename func_t,
                typename func2_t>
            struct on_each_arg_impl
            {
                meta::remove_all<func_t> func;
                meta::remove_all<func2_t> func2;

                template<
                    typename ... args_t>
                constexpr decltype(auto)
                operator()(
                    args_t&&... _args) const
                {
                    return func(func2(perfect<args_t>(_args))...);
                }
            };

            template<
                typename func_t,
                typename func2_t>
            constexpr auto
            operator()(
                func_t&& _func,
                func2_t&& _func2) const
            {
                return as_functor(on_each_arg_impl<func_t, func2_t>{
                        perfect<func_t>(_func),
                        perfect<func2_t>(_func2)});
            }
        };
    }

    extern constexpr auto on = as_functor(detail::on_impl{});




    template<
        typename operator_t,
        typename left_t,
        typename right_t>
    struct boperator_params
    {
        operator_t m_operation;
        left_t m_left;
        right_t m_right;

        template<
            typename ... args_t>
        constexpr decltype(auto)
        operator ()(
            args_t&&... _args) const
        {
            return m_operation(
                    m_left(perfect<args_t>(_args)...),
                    m_right(perfect<args_t>(_args)...));
        }
    };


    template<
        typename operator_t,
        typename right_t>
    struct uoperator_param
    {

        operator_t m_operation;
        right_t m_right;

        template<
            typename ... args_t>
        constexpr decltype(auto)
        operator ()(
            args_t&&... _args) const
        {
            return m_operation(m_right(perfect<args_t>(_args)...));
        }
    };
}







#  define ATOM_BINARY_OP_CONSTEXPR(name, symbol)                            \
struct name                                                                    \
{                                                                            \
    template<                                                                \
        typename left_t,                                                    \
        typename right_t>                                                    \
    constexpr decltype(auto)                                                \
    operator()(                                                                \
        left_t&& _left,                                                        \
        right_t&& _right) const                                                \
    {                                                                        \
        return perfect<left_t>(_left)                                        \
        symbol perfect<right_t>(_right);                                    \
    }                                                                        \
};                                                                            \
                                                                            \
                                                                            \
template<                                                                    \
    typename base_t,                                                        \
    typename base2_t>                                                        \
constexpr decltype(auto)                                                    \
operator symbol(                                                            \
    functor<base_t> const& _functor,                                        \
    functor<base2_t> const& _functor2)                                        \
{                                                                            \
    return as_functor(                                                        \
            boperator_params<                                                \
                name,                                                       \
                functor<base_t>,                                            \
                functor<base2_t>>{name{},                                    \
                                  _functor, _functor2});                      \
}                                                                            \
                                                                            \
template<                                                                    \
    typename base_t,                                                        \
    typename base2_t>                                                        \
constexpr decltype(auto)                                                    \
operator symbol(                                                            \
    functor<base_t>&& _functor,                                                \
    functor<base2_t>&& _functor2)                                            \
{                                                                            \
    return as_functor(                                                        \
            boperator_params<                                                \
                name,                                                       \
                functor<base_t>,                                            \
                functor<base2_t>>{name{},                                    \
                                  _functor, _functor2});                      \
}                                                                            \
                                                                            \
template<                                                                    \
    typename base_t,                                                        \
    typename base2_t>                                                        \
constexpr decltype(auto)                                                    \
operator symbol(                                                            \
    functor<base_t> && _functor,                                             \
    functor<base2_t> const& _functor2)                                        \
{                                                                            \
    return as_functor(                                                        \
            boperator_params<                                                \
                name,                                                       \
                functor<base_t>,                                            \
                functor<base2_t>>{name{},                                    \
                                  _functor, _functor2});                      \
}                                                                            \
                                                                            \
template<                                                                    \
    typename base_t,                                                        \
    typename base2_t>                                                        \
constexpr decltype(auto)                                                    \
operator symbol(                                                            \
    functor<base_t> const& _functor,                                        \
    functor<base2_t> && _functor2)                                            \
{                                                                            \
    return as_functor(                                                        \
            boperator_params<                                                \
                name,                                                       \
                functor<base_t>,                                            \
                functor<base2_t>>{name{},                                    \
                                  _functor, _functor2});                      \
}                                                                            \







#  define ATOM_UNARY_OP_CONSTEXPR(name, symbol)              \
struct name                                                     \
{                                                             \
    template<                                                 \
        typename right_t>                                     \
    constexpr decltype(auto)                                 \
    operator()(right_t&& _right) const                         \
    {                                                         \
        return symbol perfect<right_t>(_right);                 \
    }                                                         \
};                                                             \
                                                                         \
template<                                                     \
    typename base_t>                                         \
constexpr decltype(auto)                                     \
operator symbol(                                             \
    functor<base_t> const& _functor)                         \
{                                                             \
    return as_functor(                                         \
            uoperator_param<                                 \
                name,                                         \
                functor<base_t>>{name{},                     \
                         _functor});                         \
}                                                             \
                                                             \
template<                                                     \
    typename base_t>                                         \
constexpr decltype(auto)                                     \
operator symbol(                                             \
    functor<base_t> && _functor)                             \
{                                                             \
    return as_functor(                                         \
            uoperator_param<                                 \
                name,                                         \
                functor<base_t>>{name{},                     \
                         _functor});                         \
}                                                             \


namespace thodd
{
    /// Arithmetics
    ATOM_UNARY_OP_CONSTEXPR(inc, ++)
    ATOM_UNARY_OP_CONSTEXPR(dec, --)
    ATOM_UNARY_OP_CONSTEXPR(negate, -)
    ATOM_UNARY_OP_CONSTEXPR(positive, +)

    ATOM_BINARY_OP_CONSTEXPR(plus, +)
    ATOM_BINARY_OP_CONSTEXPR(minus, -)
    ATOM_BINARY_OP_CONSTEXPR(multiplies, *)
    ATOM_BINARY_OP_CONSTEXPR(divides, /)
    ATOM_BINARY_OP_CONSTEXPR(modulo, %)

    /// Logics
    ATOM_BINARY_OP_CONSTEXPR(equal, ==)
    ATOM_BINARY_OP_CONSTEXPR(not_equal, !=)
    ATOM_BINARY_OP_CONSTEXPR(greater, >)
    ATOM_BINARY_OP_CONSTEXPR(less, <)
    ATOM_BINARY_OP_CONSTEXPR(greater_equal, >=)
    ATOM_BINARY_OP_CONSTEXPR(less_equal, <=)
    ATOM_BINARY_OP_CONSTEXPR(bit_and, &)
    ATOM_BINARY_OP_CONSTEXPR(bit_or, |)
    ATOM_BINARY_OP_CONSTEXPR(bit_xor, ^)
    ATOM_BINARY_OP_CONSTEXPR(and_, &&)
    ATOM_BINARY_OP_CONSTEXPR(or_, ||)

    ATOM_UNARY_OP_CONSTEXPR(not_, !)
    ATOM_UNARY_OP_CONSTEXPR(bit_not, ~)

    /// Affectations
    ATOM_BINARY_OP_CONSTEXPR(plus_affect, +=)
    ATOM_BINARY_OP_CONSTEXPR(minus_affect, -=)
    ATOM_BINARY_OP_CONSTEXPR(multiplies_affect, *=)
    ATOM_BINARY_OP_CONSTEXPR(divides_affect, /=)
    ATOM_BINARY_OP_CONSTEXPR(modulo_affect, %=)
    ATOM_BINARY_OP_CONSTEXPR(lshift_affect, <<=)
    ATOM_BINARY_OP_CONSTEXPR(rshift_affect, >>=)

    /// Flux
    ATOM_BINARY_OP_CONSTEXPR(lshift, <<)
    ATOM_BINARY_OP_CONSTEXPR(rshift, >>)

    /// Access
    ATOM_UNARY_OP_CONSTEXPR(addressof, &)
    ATOM_UNARY_OP_CONSTEXPR(valueof, *)




    namespace detail
    {
        /// Placeholder_localization
        /// enables to find the nth
        /// arguments of a arguments list
        template<
            size_t index_c>
        struct placeholder_localization
        {
            template<
                typename     arg_t,
                typename ... args_t>
            constexpr decltype(auto)
            operator()(
                arg_t&& _arg,
                args_t&&... _args) const
            {

                static_assert(index_c >=0 ,
                        "template <size_t index_c> placeholder_localization : "
                        "the index must be positive or null");

                /// Recursive constexpr call
                /// until the terminal case
                return placeholder_localization<index_c-1>{}(perfect<args_t>(_args)...);
            }
        };


        /// Terminal case of localization
        /// an argument in a list of
        /// arguments
        template<>
        struct placeholder_localization <0>
        {
            template<
                typename arg_t,
                typename ... args_t>
            constexpr decltype(auto)
            operator()(
                arg_t&& _arg,
                args_t&&... _args) const
            {
                return perfect<arg_t>(_arg);
            }
        };
    }


    /// Build a placeholder
    /// localization given
    /// an index
    struct placeholder
    {
        template<
            typename  index_t>
        constexpr decltype(auto)
        operator()(
            index_t const&) const
        {
            return detail::placeholder_localization<index_t::value>{};
        }
    };

    extern constexpr auto $$  = placeholder{};
    extern constexpr auto $0  = as_functor($$(iint_0));
    extern constexpr auto $1  = as_functor($$(iint_1));
    extern constexpr auto $2  = as_functor($$(iint_2));
    extern constexpr auto $3  = as_functor($$(iint_3));
    extern constexpr auto $4  = as_functor($$(iint_4));
    extern constexpr auto $5  = as_functor($$(iint_5));
    extern constexpr auto $6  = as_functor($$(iint_6));
    extern constexpr auto $7  = as_functor($$(iint_7));
    extern constexpr auto $8  = as_functor($$(iint_8));
    extern constexpr auto $9  = as_functor($$(iint_9));
    extern constexpr auto $10 = as_functor($$(iint_10));
    extern constexpr auto $11 = as_functor($$(iint_11));
    extern constexpr auto $12 = as_functor($$(iint_12));
    extern constexpr auto $13 = as_functor($$(iint_13));
    extern constexpr auto $14 = as_functor($$(iint_14));


    /// f(inc_plh($0), inc_plh(val(...)), inc_plh($2)) <=> f($1, val(...), $3) ;

    template<
        long long offset_c>
    struct placeholder_shift
    {
        template<
            size_t index_c>
        constexpr functor<detail::placeholder_localization<index_c + offset_c>>
        operator()(
            functor<detail::placeholder_localization<index_c>> const&) const
        {
            return {};
        }

        template<
            typename type_t>
        constexpr auto
        operator() (
            type_t&& __t) const
        ->  decltype(auto)
        {
            return __t;
        }
    };

    template<
        long long offset_c>
    extern constexpr auto shift = placeholder_shift<offset_c>{};

    extern constexpr auto cout_  = ref(std::cout);
    extern constexpr auto wcout_ = ref(std::wcout);

    extern constexpr auto cin_   = ref(std::cin);
    extern constexpr auto wcin_  = ref(std::wcin);

	extern constexpr auto cerr_  = ref(std::cerr);
    extern constexpr auto wcerr_ = ref(std::wcerr);



    namespace detail
    {
        using cout_char = typename decltype(std::cout)::char_type;
        using cout_traits = typename decltype(std::cout)::traits_type;

        using wcout_char = typename decltype(std::wcout)::char_type;
        using wcout_traits = typename decltype(std::wcout)::traits_type;
    }

#  define ARGON_COMPLEX_STREAMFLAG(name)                                          \
    extern constexpr auto name##_  = cref(std::name<detail::cout_char, detail::cout_traits>);      \
    extern constexpr auto w##name##_ = cref(std::name<detail::wcout_char, detail::wcout_traits>);  \


    ARGON_COMPLEX_STREAMFLAG(endl)
    ARGON_COMPLEX_STREAMFLAG(flush)
    ARGON_COMPLEX_STREAMFLAG(ends)


#  define ARGON_SIMPLE_STREAMFLAG(name) \
	extern constexpr auto name##_ = cref(std::name);     \

    ARGON_SIMPLE_STREAMFLAG(boolalpha)
    ARGON_SIMPLE_STREAMFLAG(showbase)
    ARGON_SIMPLE_STREAMFLAG(noshowbase)
    ARGON_SIMPLE_STREAMFLAG(showpoint)
    ARGON_SIMPLE_STREAMFLAG(noshowpoint)
    ARGON_SIMPLE_STREAMFLAG(showpos)
    ARGON_SIMPLE_STREAMFLAG(skipws)
    ARGON_SIMPLE_STREAMFLAG(noskipws)
    ARGON_SIMPLE_STREAMFLAG(uppercase)
    ARGON_SIMPLE_STREAMFLAG(nouppercase)
    ARGON_SIMPLE_STREAMFLAG(unitbuf)
    ARGON_SIMPLE_STREAMFLAG(nounitbuf)
    ARGON_SIMPLE_STREAMFLAG(left)
    ARGON_SIMPLE_STREAMFLAG(right)
    ARGON_SIMPLE_STREAMFLAG(internal)
    ARGON_SIMPLE_STREAMFLAG(dec)
    ARGON_SIMPLE_STREAMFLAG(hex)
    ARGON_SIMPLE_STREAMFLAG(oct)
    ARGON_SIMPLE_STREAMFLAG(fixed)
    ARGON_SIMPLE_STREAMFLAG(scientific)
    ARGON_SIMPLE_STREAMFLAG(hexfloat)
    ARGON_SIMPLE_STREAMFLAG(defaultfloat)




    namespace detail
    {
        struct until_impl
        {
            template<
                typename cond_t>
            struct until_cond_impl
            {
                meta::remove_all<cond_t> cond;


                template<
                    typename then_t>
                struct until_cond_then_impl
                {
                    meta::remove_all<cond_t> cond;
                    meta::remove_all<then_t> then;

                    template<
                        typename ... args_t>
                    constexpr void
                    operator()(
                        args_t&&... _args) const
                    {
                        while(!cond(perfect<args_t>(_args)...))
                            then(perfect<args_t>(_args)...);
                    }
                };


                template<
                    typename then_t>
                constexpr decltype(auto)
                operator()(
                    then_t&& _then) const
                {
                    return until_cond_then_impl<then_t>{cond, perfect<then_t>(_then)};
                }

            };

            template<
                typename cond_t>
            constexpr decltype(auto)
            operator()(
                cond_t&& _cond) const
            {
                return as_functor(until_cond_impl<cond_t>{
                    perfect<cond_t>(_cond)});
            }
        };
    }

    extern constexpr auto until_ = as_functor(detail::until_impl{});




    namespace detail
    {
        struct while_impl
        {
            template<
                typename cond_t>
            struct while_cond_impl
            {
                meta::remove_all<cond_t> cond;


                template<
                    typename then_t>
                struct while_cond_then_impl
                {
                    meta::remove_all<cond_t> cond;
                    meta::remove_all<then_t> then;

                    template<
                        typename ... args_t>
                    constexpr void
                    operator()(
                        args_t&&... _args) const
                    {
                        while(cond(perfect<args_t>(_args)...))
                            then(perfect<args_t>(_args)...);
                    }
                };

                template<
                    typename then_t>
                constexpr decltype(auto)
                operator()(
                    then_t&& _then) const
                {
                    return while_cond_then_impl<then_t>{cond, perfect<then_t>(_then)};
                }

            };

            template<
                typename cond_t>
            constexpr decltype(auto)
            operator()(
                cond_t&& _cond) const
            {
                return as_functor(while_cond_impl<cond_t>{
                    perfect<cond_t>(_cond)});
            }
        };
    }

    extern constexpr auto while_ = as_functor(detail::while_impl{});





    namespace detail
    {
        struct static_cast_builder
        {
            template<
                typename type_t>
            struct static_cast_impl
            {
                template<
                    typename args_t>
                constexpr type_t
                operator()(
                    args_t&& _args) const
                {
                    return static_cast<type_t>(_args);
                }
            };

            template<
                typename type_t>
            constexpr auto
            operator()(
                type_<type_t> const&) const
            {
                return as_functor(static_cast_impl<type_t>{});
            }
        };
    }

    extern constexpr auto static_cast_ = detail::static_cast_builder{};


    namespace detail
    {
        struct partial_builder
        {
            template<
                typename func_t, 
                typename ... bindeds_t>
            struct partial_impl
            {
                func_t func;
                
                tuple<bindeds_t...> bindeds;

                template<
                    typename ... args_t>
                constexpr decltype(auto) 
                operator()(
                    args_t&&... __args) const
                {
                    return (*this).eval(
                                make_indexes<sizeof...(bindeds_t)>{}, 
                                make_indexes<sizeof...(args_t) - sizeof...(bindeds_t)>{}, 
                                perfect<args_t>(__args)...);
                }

                template<
                    size_t ... bindeds_indexes_c,
                    size_t ... other_indexes_c, 
                    typename ... args_t>
                constexpr decltype(auto) 
                eval( 
                    indexes<bindeds_indexes_c...> const&,
                    indexes<other_indexes_c...> const&,
                    args_t&&... __args) const
                {
                    return func(bindeds.template get<bindeds_indexes_c>()(perfect<args_t>(__args)...)..., 
                                  as_functor($$(iint_<other_indexes_c>{}))(perfect<args_t>(__args)...)...);
                }

            };

            template<
                typename func_t, 
                typename ... bindeds_t>
            constexpr auto
            operator()(
                func_t&& __func,
                bindeds_t&&... __bindeds) const
            {
                return as_functor(partial_impl<func_t, bindeds_t...> {perfect<func_t>(__func), 
                                                                      make_tuple(perfect<bindeds_t>(__bindeds)...)});
            }
        };
    }
}

#endif /* ATOM_FUNCTIONAL_HPP_ */
