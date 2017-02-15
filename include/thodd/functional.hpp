/*
 * functional.hpp
 *
 *  Created on: 13 sept. 2016
 *      Author: Benjamin
 */
 
#ifndef THODD_FUNCTIONAL_HPP_
#  define THODD_FUNCTIONAL_HPP_

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

    extern constexpr auto 
    nothing = as_functor([](auto&&... __args) {});

    struct id
    {
        constexpr auto 
        operator()(auto&&...) {}
    };

    extern constexpr auto 
    always = 
        [] (auto&& __arg)
        {
            return as_functor(
            [__arg](auto&&... __args)
            -> decltype(auto)
            {
                return __arg;
            });
        };

    extern constexpr auto 
    demux = 
        [](auto&& __func)
        {
            return 
            [&__func](auto&&... __funcs)
            {
                return as_functor( 
                [__func, __funcs...](auto&&... __args)
                -> decltype(auto)
                {
                    return __func(__funcs(perfect<decltype(__args)>(__args)...)...);
                });
            };
        };

    extern constexpr auto
    compose = 
        [](auto&& __fsup, auto&& __finf) 
        {
            return as_functor(
                demux(perfect<decltype(__fsup)>(__fsup))
                (perfect<decltype(__finf)>(__finf)));
        };

    extern constexpr auto
    bind = 
        [](auto&& __func, auto&&... __funcs) 
        {
            return as_functor(
                demux(perfect<decltype(__func)>(__func))
                (perfect<decltype(__funcs)>(__funcs)...));  
        };

    extern constexpr auto
	member = 
        [](auto&& _func, auto&& _instance, auto&&... _prebinded)
        {
            return as_functor(
            [=](auto&&... _args) 
            ->decltype(auto)
            {
                using func_t = decltype(_func);
                using instance_t = decltype(_instance);

                return (perfect<instance_t>(_instance).*perfect<func_t>(_func))(_prebinded(perfect<decltype(_args)>(_args)...)...);
            });
        };

    extern constexpr auto
    partial = 
        [](auto&& __func, auto&&... __params)
        {
            return as_functor(
            [__func, &__params...](auto&&... __args)
            -> decltype(auto)
            {
                return 
                __func(perfect<decltype(__params)>(__params)..., 
                       perfect<decltype(__args)>(__args)...);
            });
        };



    extern constexpr auto
    rpartial = 
        [](auto&& __func, auto&&... __params)
        {
            return as_functor(
            [__func, &__params...](auto&&... __args)
            -> decltype(auto)
            {
                return 
                __func(perfect<decltype(__args)>(__args)..., 
                       perfect<decltype(__params)>(__params)...);
            });
        };

    extern constexpr auto 
    on = 
        [](auto&& __func, auto&& __applied)
        {
            return as_functor( 
            [__func, __applied](auto&&... __args)
            -> decltype(auto)
            {
                return __func(__applied(perfect<decltype(__args)>(__args))...);
            });
        };

    template<
        typename type_t>
    extern constexpr auto 
    cast_ = as_functor(
        [](auto&& __arg)
        -> decltype(auto)
        {
            return (type_t) (perfect<decltype(__arg)>(__arg));
        }); 

    template<
        typename type_t>
    extern constexpr auto 
    static_cast_ = as_functor(
        [](auto&& __arg)
        -> decltype(auto)
        {
            return static_cast<type_t>(perfect<decltype(__arg)>(__arg));
        }); 

    template<
        typename type_t>
    extern constexpr auto 
    dynamic_cast_ = as_functor(
        [](auto&& __arg)
        -> decltype(auto)
        {
            return dynamic_cast<type_t>(perfect<decltype(__arg)>(__arg));
        }); 

    template<
        typename type_t>
    extern constexpr auto 
    const_cast_ = as_functor(
        [](auto&& __arg)
        -> decltype(auto)
        {
            return const_cast<type_t>(perfect<decltype(__arg)>(__arg));
        });

    template<
        typename type_t>
    extern constexpr auto 
    reinterpret_cast_ = as_functor(
        [](auto&& __arg)
        -> decltype(auto)
        {
            return reinterpret_cast<type_t>(perfect<decltype(__arg)>(__arg));
        });

    
    extern constexpr auto
    fix = 
        [](auto&& __func)
        {
            return as_functor(
            [__func](auto&&... __args)
            -> decltype(auto)
            {
                return 
                __func(
                    fix(__func), 
                    perfect<decltype(__args)>(__args)...);
            });
        };

    
    extern constexpr auto
    ref = 
        [](auto& __ref)
        {
            return as_functor(
            [&__ref](auto&&... __args)
            -> decltype(auto)
            {
                return __ref;
            });
        };


    extern constexpr auto
    cref = 
        [](auto const& __cref)
        {
            return as_functor(
            [&__cref] (auto&&... __args)
            -> decltype(auto)
            {
                return __cref;
            });
        };


    extern constexpr auto
    val = 
        [](auto&& __val)
        {
            return as_functor(
            [__val](auto&&... __args)
            -> decltype(auto)
            {
                return __val;
            });
        };

     template<
        size_t index_c>
    constexpr auto 
    placeholder()
    {
        return 
        [](auto&& __arg, auto&&... __args)
        -> decltype(auto)
        {
            constexpr auto __subrank = placeholder<index_c - 1>(); 
            return __subrank(perfect<decltype(__args)>(__args)...);
        };
    }


    template<> 
    constexpr auto 
    placeholder<0>()
    {
        return 
        [](auto&& __arg, auto&&... __args)
        -> decltype(auto)
        {
            return __arg;
        };
    }

    extern constexpr auto $0  = as_functor(placeholder<0>());
    extern constexpr auto $1  = as_functor(placeholder<1>());
    extern constexpr auto $2  = as_functor(placeholder<2>());
    extern constexpr auto $3  = as_functor(placeholder<3>());
    extern constexpr auto $4  = as_functor(placeholder<4>());
    extern constexpr auto $5  = as_functor(placeholder<5>());
    extern constexpr auto $6  = as_functor(placeholder<6>());
    extern constexpr auto $7  = as_functor(placeholder<7>());
    extern constexpr auto $8  = as_functor(placeholder<8>());
    extern constexpr auto $9  = as_functor(placeholder<9>());
    extern constexpr auto $10  = as_functor(placeholder<10>());
    extern constexpr auto $11  = as_functor(placeholder<11>());
    extern constexpr auto $12  = as_functor(placeholder<12>());
    extern constexpr auto $13  = as_functor(placeholder<13>());
    extern constexpr auto $14  = as_functor(placeholder<14>());
    extern constexpr auto $15  = as_functor(placeholder<15>());


    template<
        typename builder_t>
    struct statement
    {
         builder_t builder;

        constexpr auto
        operator[] (
            auto&& __statements) const
        {
            return 
              builder(
                perfect<decltype(__statements)>(__statements));
        }
    };

    
    constexpr auto
    as_statement(
        auto&& __builder)
    {
        return statement<meta::decay<decltype(__builder)>>{__builder}; 
    }

    extern constexpr auto
    while_ = 
        [](auto&& __cond)
        {
            return 
            as_statement(
            [&__cond] (auto&& __statements)
            {
                return as_functor(
                [__cond, __statements](auto&&... __args)
                {
                    while(__cond(perfect<decltype(__args)>(__args)...))
                        __statements(perfect<decltype(__args)>(__args)...);
                });
            });
        };

    extern constexpr auto
    until_ = 
        [](auto&& __cond)
        {
            return 
            as_statement(
            [&__cond] (auto&& __statements)
            {
                return as_functor(
                [__cond, __statements](auto&&... __args)
                {
                    while(!__cond(perfect<decltype(__args)>(__args)...))
                        __statements(perfect<decltype(__args)>(__args)...);
                });
            });
        };
    

    extern constexpr auto
    if_ = 
        [](auto&& __cond)
        {
            return 
            as_statement(
            [&__cond] (auto&& __statements)
            {
                return as_functor(
                [__cond, __statements](auto&&... __args)
                {
                    if(__cond(perfect<decltype(__args)>(__args)...))
                        __statements(perfect<decltype(__args)>(__args)...);
                });
            });
        };

    extern constexpr auto
    tern = 
        [](auto&& __cond)
        {
            return 
            as_statement(
            [&__cond] (auto&& __statements)
            {
                return 
                as_statement(
                [&__cond, &__statements](auto&& __else_statements)
                {
                    return as_functor(
                    [__cond, __statements, __else_statements](auto&&... __args)
                    -> decltype(auto)
                    {
                        return 
                            __cond(perfect<decltype(__args)>(__args)...) ?
                             __statements(perfect<decltype(__args)>(__args)...) :
                             __else_statements(perfect<decltype(__args)>(__args)...);
                    });
                });
            });
        };




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







#  define THODD_BINARY_OP_CONSTEXPR(name, symbol)         \
struct name                                              \
{                                                        \
    template<                                            \
        typename left_t,                                 \
        typename right_t>                                \
    constexpr decltype(auto)                             \
    operator()(                                          \
        left_t&& _left,                                  \
        right_t&& _right) const                          \
    {                                                    \
        return perfect<left_t>(_left)                    \
        symbol perfect<right_t>(_right);                 \
    }                                                    \
};                                                       \
                                                         \
                                                         \
template<                                                \
    typename base_t,                                     \
    typename base2_t>                                    \
constexpr decltype(auto)                                 \
operator symbol(                                         \
    functor<base_t> const& _functor,                     \
    functor<base2_t> const& _functor2)                   \
{                                                        \
    return as_functor(                                   \
            boperator_params<                            \
                name,                                    \
                functor<base_t>,                         \
                functor<base2_t>>{name{},                \
                                  _functor, _functor2}); \
}                                                        \
                                                         \
template<                                                \
    typename base_t,                                     \
    typename base2_t>                                    \
constexpr decltype(auto)                                 \
operator symbol(                                         \
    functor<base_t>&& _functor,                          \
    functor<base2_t>&& _functor2)                        \
{                                                        \
    return as_functor(                                   \
            boperator_params<                            \
                name,                                    \
                functor<base_t>,                         \
                functor<base2_t>>{name{},                \
                                  _functor, _functor2}); \
}                                                        \
                                                         \
template<                                                \
    typename base_t,                                     \
    typename base2_t>                                    \
constexpr decltype(auto)                                 \
operator symbol(                                         \
    functor<base_t> && _functor,                         \
    functor<base2_t> const& _functor2)                   \
{                                                        \
    return as_functor(                                   \
            boperator_params<                            \
                name,                                    \
                functor<base_t>,                         \
                functor<base2_t>>{name{},                \
                                  _functor, _functor2}); \
}                                                        \
                                                         \
template<                                                \
    typename base_t,                                     \
    typename base2_t>                                    \
constexpr decltype(auto)                                 \
operator symbol(                                         \
    functor<base_t> const& _functor,                     \
    functor<base2_t> && _functor2)                       \
{                                                        \
    return as_functor(                                   \
            boperator_params<                            \
                name,                                    \
                functor<base_t>,                         \
                functor<base2_t>>{name{},                \
                                  _functor, _functor2}); \
}                                                        \






#  define THODD_UNARY_OP_CONSTEXPR(name, symbol)     \
struct name                                         \
{                                                   \
    template<                                       \
        typename right_t>                           \
    constexpr decltype(auto)                        \
    operator()(right_t&& _right) const              \
    {                                               \
        return symbol perfect<right_t>(_right);     \
    }                                               \
};                                                  \
                                                    \
template<                                           \
    typename base_t>                                \
constexpr decltype(auto)                            \
operator symbol(                                    \
    functor<base_t> const& _functor)                \
{                                                   \
    return as_functor(                              \
            uoperator_param<                        \
                name,                               \
                functor<base_t>>{name{},            \
                         _functor});                \
}                                                   \
                                                    \
template<                                           \
    typename base_t>                                \
constexpr decltype(auto)                            \
operator symbol(                                    \
    functor<base_t> && _functor)                    \
{                                                   \
    return as_functor(                              \
            uoperator_param<                        \
                name,                               \
                functor<base_t>>{name{},            \
                         _functor});                \
}                                                   \


namespace thodd
{
    /// Arithmetics
    THODD_UNARY_OP_CONSTEXPR(inc, ++)
    THODD_UNARY_OP_CONSTEXPR(dec, --)
    THODD_UNARY_OP_CONSTEXPR(negate, -)
    THODD_UNARY_OP_CONSTEXPR(positive, +)

    THODD_BINARY_OP_CONSTEXPR(plus, +)
    THODD_BINARY_OP_CONSTEXPR(minus, -)
    THODD_BINARY_OP_CONSTEXPR(multiplies, *)
    THODD_BINARY_OP_CONSTEXPR(divides, /)
    THODD_BINARY_OP_CONSTEXPR(modulo, %)

    /// Logics
    THODD_BINARY_OP_CONSTEXPR(equal, ==)
    THODD_BINARY_OP_CONSTEXPR(not_equal, !=)
    THODD_BINARY_OP_CONSTEXPR(greater, >)
    THODD_BINARY_OP_CONSTEXPR(less, <)
    THODD_BINARY_OP_CONSTEXPR(greater_equal, >=)
    THODD_BINARY_OP_CONSTEXPR(less_equal, <=)
    THODD_BINARY_OP_CONSTEXPR(bit_and, &)
    THODD_BINARY_OP_CONSTEXPR(bit_or, |)
    THODD_BINARY_OP_CONSTEXPR(bit_xor, ^)
    THODD_BINARY_OP_CONSTEXPR(and_, &&)
    THODD_BINARY_OP_CONSTEXPR(or_, ||)

    THODD_UNARY_OP_CONSTEXPR(not_, !)
    THODD_UNARY_OP_CONSTEXPR(bit_not, ~)

    /// Affectations
    THODD_BINARY_OP_CONSTEXPR(plus_affect, +=)
    THODD_BINARY_OP_CONSTEXPR(minus_affect, -=)
    THODD_BINARY_OP_CONSTEXPR(multiplies_affect, *=)
    THODD_BINARY_OP_CONSTEXPR(divides_affect, /=)
    THODD_BINARY_OP_CONSTEXPR(modulo_affect, %=)
    THODD_BINARY_OP_CONSTEXPR(lshift_affect, <<=)
    THODD_BINARY_OP_CONSTEXPR(rshift_affect, >>=)

    /// Flux
    THODD_BINARY_OP_CONSTEXPR(lshift, <<)
    THODD_BINARY_OP_CONSTEXPR(rshift, >>)

    /// Access
    THODD_UNARY_OP_CONSTEXPR(addressof, &)
    THODD_UNARY_OP_CONSTEXPR(valueof, *)





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

}

#endif /* THODD_FUNCTIONAL_HPP_ */
