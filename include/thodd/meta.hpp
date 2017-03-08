#ifndef THODD_META_HPP_
#  define THODD_META_HPP_

#  include <thodd/meta_sequence.hpp>

namespace thodd
{

    using unsigned_t  = unsigned long long;

    /// enables to add
    /// type member to
    /// any class by
    /// inheritance
    template<
        typename type_t>
    struct type_
    {
        using type = type_t;
    };




    /// Access to
    /// type member
    /// of type_t.
    template<
        typename type_t>
    using __type = typename type_t::type;




    /// enables to add
    /// value and value_type
    /// member to any class
    /// by inheritance
    template<
        typename value_t,
        value_t value_c>
    struct value_
    {
        using value_type = value_t;
        static constexpr value_t value{value_c};

        constexpr auto
        operator()() const
        {
            return value;
        }
    };




    /// Access to
    /// value_type member
    /// of type_t.
    template<
        typename type_t>
    using __value_type = typename type_t::value_type;



    /// enables to access
    /// to the next member
    /// of type_t
    template<
        typename type_t>
    using __next = typename type_t::next;




    template<
        typename type_t,
        type_t _value>
    struct integral_constant:
        type_<integral_constant<type_t, _value>>,
        value_<type_t, _value> {};


    template<
        typename type_t,
        type_t _value>
    using igral = integral_constant<type_t, _value>;


    /// Wrapper for bool
    template<bool _b>
    using ibool_ =
        igral<bool, _b>;

    /// Wrapper for short
    template<short _s>
    using ishort_ =
        igral<short, _s>;

    /// Wrapper for unsigned short
    template<unsigned short _us>
    using iushort_ =
        igral<unsigned short, _us>;

    /// Wrapper for char
    template<char _c>
    using ichar_ =
        igral<char, _c>;

    /// Wrapper for char
    template<char _c>
    using iwchar_ =
        igral<wchar_t, _c>;

    /// Wrapper for char
    template<char _c>
    using ichar16_ =
        igral<char16_t, _c>;

    /// Wrapper for char
    template<char _c>
    using ichar32_ =
        igral<char32_t, _c>;

    /// Wrapper for int
    template<int _i>
    using iint_ =
        igral<int, _i>;

    /// Wrapper for long
    template<long _l>
    using ilong_ =
        igral<long, _l>;

    /// Wrapper for long long
    template<long long _ll>
    using ilonglong_ =
        igral<long long, _ll>;

    /// Wrapper for unsigned
    template<unsigned _u>
    using iunsigned_ =
        igral<unsigned, _u>;

    /// Wrapper for unsigned long
    template<unsigned long _ul>
    using iunsignedl_ =
        igral<unsigned long, _ul>;

    /// Wrapper for unsigned long long
    template<unsigned long long _ull>
    using iunsignedll_ =
        igral<unsigned long long, _ull>;

    /// Wrapper for unsigned_t
    template<unsigned_t _s>
    using isize_t_ =
        igral<unsigned_t, _s>;


    using true_ = ibool_<true>;
    using false_ = ibool_<false>;


    constexpr auto iint_0 = iint_<0>{};
    constexpr auto iint_1 = iint_<1>{};
    constexpr auto iint_2 = iint_<2>{};
    constexpr auto iint_3 = iint_<3>{};
    constexpr auto iint_4 = iint_<4>{};
    constexpr auto iint_5 = iint_<5>{};
    constexpr auto iint_6 = iint_<6>{};
    constexpr auto iint_7 = iint_<7>{};
    constexpr auto iint_8 = iint_<8>{};
    constexpr auto iint_9 = iint_<9>{};
    constexpr auto iint_10 = iint_<10>{};
    constexpr auto iint_11 = iint_<11>{};
    constexpr auto iint_12 = iint_<12>{};
    constexpr auto iint_13 = iint_<13>{};
    constexpr auto iint_14 = iint_<14>{};





    namespace meta
    {
        namespace lazy
        {
            

           









            template<
                typename type_t>
            struct is_arithmetic:
                    or_<is_floating_point<type_t>,
                        is_integral<type_t>> {};




            template<
                typename type_t>
            struct is_fundamental:
                    or_<is_arithmetic<type_t>,
                        is_void<type_t>,
                        is_null_ptr<type_t>> {};




            template<
                typename type_t>
            struct is_scalar:
                    or_<is_arithmetic<type_t>,
                        is_enum<type_t>,
                        is_pointer<type_t>,
                        is_member_pointer<type_t>,
                        is_null_ptr<type_t>> {};




            template<
                typename type_t>
            struct is_object:
                    or_<is_scalar<type_t>,
                        is_array<type_t>,
                        is_union<type_t>,
                        is_class<type_t>> {};




            template<
                typename type_t>
            struct is_compound:
                    not_<is_fundamental<type_t>> {};








        namespace lazy
        {
            template<
                typename _From, 
                typename _To,
                bool = or_<
                        is_void<_From>, 
                        is_function<_To>,
                        is_array<_To>>::value>
            struct __is_convertible_helper
            { 
                typedef typename is_void<_To>::type type; 
            };

            template<typename _From, typename _To>
            class __is_convertible_helper<_From, _To, false>
            {
                template<
                    typename _To1>
                static void __test_aux(_To1);

                template<
                    typename _From1, 
                    typename _To1,
                    typename = decltype(__test_aux<_To1>(std::declval<_From1>()))>
                static true_
                __test(int);

                template<
                    typename, 
                    typename>
                static false_
                __test(...);

                public:
                    typedef decltype(__test<_From, _To>(0)) type;
            };


            /// is_convertible
            template<typename _From, typename _To>
            struct is_convertible : 
                public __is_convertible_helper<_From, _To>::type
            {
            };
        }


        template<
            typename from_t, 
            typename to_t>
        using is_convertible = __type<lazy::is_convertible<from_t, to_t>>;




        namespace lazy
        {
            template<
                bool predicate_c, 
                typename then_t, 
                typename else_t>
            struct if_;

            template<   
                typename then_t, 
                typename else_t>
            struct if_<true, then_t, else_t>
            {
                using type = then_t;
            };

            template<   
                typename then_t, 
                typename else_t>
            struct if_<false, then_t, else_t>
            {
                using type = else_t;
            };
        }

        
        template<
            typename predicate_t, 
            typename then_t, 
            typename else_t>
        using if_ = __type<lazy::if_<predicate_t::value, then_t, else_t>>;






        /// //// ///
        /// Pack ///
        /// //// ///


        template<
            typename ... types_t>
        struct pack:
                type_<pack<types_t...>>
        {
            typedef isize_t_<sizeof...(types_t)> size;
        };

        template<
            typename ... types_t>
        using decayed_pack = pack<decay<types_t>...>;




        namespace lazy
        {
            template<
                typename pack_t,
                template<typename ...> typename topack_t>
            struct transfer;

            template<
                template<typename ...> class pack_t,
                typename ... types_t,
                template<typename ...> class topack_t>
            struct transfer<pack_t<types_t...>, topack_t>
            {
                using type = topack_t<types_t...>;
            };
        }


        template<
            typename pack_t, 
            template<typename ...> typename topack_t>
        using transfer = __type<lazy::transfer<pack_t, topack_t>>;



        namespace lazy
        {
            template<
                template<typename...> class pack_t,
                typename type_t,
                size_t nb_c>
            struct repeat
            {
                template<
                    typename indexes_t>
                struct repeat_impl;

                template<
                    size_t ... indexes_c>
                struct repeat_impl<indexes<indexes_c...>>
                {
                    template<   
                        size_t index_c>
                    struct repeat_item
                    {
                        using type = type_t;
                    };

                    using type = pack_t<__type<repeat_item<indexes_c>>...>;
                };

                using type = __type<repeat_impl<make_indexes<nb_c>>>;
            };
        }


        template<
            template<typename...> class pack_t,
            typename type_t, 
            size_t nb_c>
        using repeat = __type<lazy::repeat<pack_t, type_t, nb_c>>;



        namespace lazy
        {
            template<
                unsigned_t idx_c,
                typename pack_t>
            struct at;

            template<
                template<typename...> class pack_t,
                typename type_t,
                typename ... types_t>
            struct at<0, pack_t<type_t, types_t...>> :
                    type_<type_t> {};

            template<
                template<typename...> class pack_t,
                unsigned_t idx_c,
                typename type_t,
                typename ... types_t>
            struct at<idx_c, pack_t<type_t, types_t...>>:
                    at<idx_c - 1, pack_t<types_t...>> {};
        }


        template<
            unsigned_t idx_c,
            typename pack_t>
        using at = __type<lazy::at<idx_c, pack_t>>;


        template<
            typename index_t,
            typename pack_t>
        constexpr auto
        at_f(
            pack_t const&)
        {
            return at<index_t::value, pack_t>{};
        }


        template<
            typename type_t,
            template<typename...> typename pack_t,
            typename ... items_t>
        constexpr pack_t<items_t..., type_t>
        push_back_f(
            type_<type_t> const&, 
            pack_t<items_t...> const&)
        {
            return {};
        }

        template<
            typename type_t, 
            typename pack_t>
        using push_back = decltype(push_back_f(type_<type_t>{}, pack_t{}));


        template<
            typename type_t,
            template<typename...> typename pack_t,
            typename ... items_t>
        constexpr pack_t<type_t, items_t...>
        push_front_f(
            type_<type_t> const&, 
            pack_t<items_t...> const&)
        {
            return {};
        }

        template<
            typename type_t, 
            typename pack_t>
        using push_front = decltype(push_front_f(type_<type_t>{}, pack_t{}));


        


        namespace lazy
        {
            template<
                typename pack_t>
            struct reverse;

            template<
                template<typename...> class  pack_t,
                typename ... items_t>
            struct reverse<pack_t<items_t...>>
            {
                template<
                    typename indexes_t>
                struct impl;

                template<
                    size_t ... indexes_c>
                struct impl<indexes<indexes_c...>>
                {
                    using type = pack_t<meta::at<indexes_c, pack_t<items_t...>>...>;
                };

                using type = __type<impl<make_rindexes<sizeof...(items_t)>>>; 
            };
        }




        template<
           typename pack_t>
        using reverse = __type<lazy::reverse<pack_t>>;

        template<
            typename pack_t>
        constexpr auto
        reverse_f(
            pack_t const&)
        {
            return reverse<pack_t>{};
        }



        namespace lazy
        {
            template<
                typename pack_t>
            struct pop_front;

            template<
                typename type_t,
                template<typename ...> class pack_t,
                typename ... types_t>
            struct pop_front<pack_t<type_t, types_t...>>:
                    pack_t<types_t...> {};
        }



        template<
            typename pack_t>
        using pop_front = __type<lazy::pop_front<pack_t>>;

        template<
            typename pack_t>
        constexpr auto
        pop_front_f(
            pack_t const&)
        {
            return pop_front<pack_t>{};
        }




        namespace lazy
        {
            template<
                typename pack_t>
            struct pop_back
            {
                using type = meta::reverse<meta::pop_front<meta::reverse<pack_t>>>;
            };
        }




        template<
            typename pack_t>
        using pop_back = __type<lazy::pop_back<pack_t>>;



        template<
            typename pack_t>
        constexpr auto
        pop_back_f(
            pack_t const&)
        {
            return pop_back<pack_t>{};
        }




        namespace lazy
        {
            template<
                typename pack1_t, 
                typename pack2_t>
            struct concat;

            template<
                template<typename ...> typename  pack1_t, 
                typename ... items1_t, 
                template<typename ...> typename pack2_t, 
                typename ... items2_t>
            struct concat<pack1_t<items1_t...>, pack2_t<items2_t...>>
            {
                using type = pack1_t<items1_t..., items2_t...>; 
            };
        }

        


        template<
            typename pack1_t, 
            typename pack2_t>
        using concat = __type<lazy::concat<pack1_t, pack2_t>>;


        namespace lazy
        {
            template<
                typename type_t, 
                typename pack_t>
            struct contains;

            template<
                typename type_t, 
                template<typename ...> class pack_t,
                typename ... types_t>
            struct contains<type_t, pack_t<types_t...>> : 
                    or_<is_same<type_t, types_t>...> {};
        }




        template<
            typename type_t, 
            typename pack_t>
        using contains = __type<lazy::contains<type_t, pack_t>>;




        namespace lazy
        {
            template<
                typename pack_t>
            struct unique;

            template<
                template<typename ...> typename pack_t, 
                typename ... items_t>
            struct unique<pack_t<items_t...>>
            {
                template<
                    typename ... to_see_t>
                struct impl;

                template<
                    typename current_t, 
                    typename next_t,
                    typename ... nexts_t>
                struct impl<current_t, next_t, nexts_t...>
                {
                    using type = meta::concat<meta::if_<meta::contains<current_t, pack_t<next_t, nexts_t...>>, pack_t<>, pack_t<current_t>>, __type<impl<next_t, nexts_t...>>>;
                };
            
                
                template<
                    typename current_t>
                struct impl<current_t>
                {
                    using type = pack_t<current_t>;
                };
                
                using type = __type<impl<items_t...>>;
            };
        }

        template<
            typename pack_t>
        using unique = __type<lazy::unique<pack_t>>;



        template<
            typename type_t, 
            typename pack_t>
        constexpr bool
        contains_f(
            type_<type_t> const&, 
            type_<pack_t> const&)
        {
            return contains<type_t, pack_t>::value;
        }


       



        template<
            typename type_t>
        struct __declval_protector
        {
            static const bool __stop = false;
            static add_rvalue_reference<type_t> __delegate();
        };

        template<
            typename type_t>
        inline add_rvalue_reference<type_t>
        declval() noexcept
        {
            static_assert(__declval_protector<type_t>::__stop,
                    "declval() must not be used!");
            return __declval_protector<type_t>::__delegate();
        }


        namespace lazy
        {
            template<
                typename func_t>
            struct is_valid_impl
            {
                template<
                    typename ... args_t,
                    typename = decltype (declval<func_t>()(declval<args_t>()...))>
                static constexpr bool
                validation_switcher(int)
                {
                    return true;
                }

                template<
                    typename ... args_t>
                static constexpr bool
                validation_switcher(...)
                {
                    return false;
                }

                template<
                    typename ... args_t>
                constexpr bool
                operator()(
                    type_<args_t>&& ...) const
                {
                    return validation_switcher<args_t...>(int{});
                }
            };
        }

        template<
            typename type_t>
        constexpr auto
        is_valid(
            type_t&&)
        {
            return lazy::is_valid_impl<type_t>{};
        }


#  define THODD_USING_MEMBER(name)                           \
        [](auto&& _t)                                       \
        -> typename meta::remove_all<decltype(_t)>::name {} \


#  define THODD_STATIC_ATTRIBUTE_MEMBER(name)           \
        [](auto&& _t)                                  \
        -> decltype(remove_all<decltype(_t)>::name) {} \


        constexpr auto has_type       = is_valid(THODD_USING_MEMBER(type));
        constexpr auto has_value_type = is_valid(THODD_USING_MEMBER(value_type));

        constexpr auto has_static_value = is_valid(THODD_STATIC_ATTRIBUTE_MEMBER(value));


        namespace lazy
        {
            template<
                bool cond_c,
                typename type_t = void>
            struct enable_if {};

            template<
                typename type_t>
            struct enable_if<true, type_t>:
                    type_<type_t> {};
        }

        template<
            bool bool_c, 
            typename type_t = void>
        using enable_if = __type<lazy::enable_if<bool_c, type_t>>;
    }
}




#endif /* THODD_META_HPP_ */
