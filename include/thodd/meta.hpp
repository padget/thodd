#ifndef THODD_META_HPP_
#  define THODD_META_HPP_

namespace thodd
{

    namespace meta
    {
        namespace lazy
        {
            

           
















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
