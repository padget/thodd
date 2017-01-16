#ifndef ATOM_META_HPP_
#  define ATOM_META_HPP_

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



    /// indexes represents
    /// a sequence of unsigned_t
    template<
        unsigned_t... _indexes>
    struct indexes final
    {
        using next = indexes<_indexes..., sizeof...(_indexes)>;
    };




    namespace detail
    {
        /// returns a indexes
        /// builded from 0
        /// up to max - 1
        template<
            unsigned_t _max>
        struct build_indexes final:
            type_<__next<__type<build_indexes<_max - 1>>>> {};

        /// 0 case for build_indexes
        template<>
        struct build_indexes<0> final:
            type_<indexes<>> {};
    }




    /// shortcut for
    /// build_indexes
    template<
        unsigned_t _max>
    using make_indexes = typename detail::build_indexes<_max>::type;



    namespace detail
    {
        /// build a reversed
        /// indexes from
        /// max - 1 to 0
        template<
            typename indexes_t>
        struct build_rindexes;

        /// expand indexes_c
        /// into the reversed
        /// structure
        template<
            unsigned_t... indexes_c>
        struct build_rindexes<indexes<indexes_c...>>:
                type_<indexes<(sizeof...(indexes_c) - 1 - indexes_c)...>> {};
    }




    /// shortcut for
    /// build_rindexes
    template<
        unsigned_t max_c>
    using make_rindexes = __type<detail::build_rindexes<make_indexes<max_c>>>;

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
        constexpr bool 
        or_f()
        {
            return false;
        }

        constexpr bool
        or_f(bool const& __v)
        {
            return __v;
        }

        template<
            typename cond_t, 
            typename ... conds_t>
        constexpr bool
        or_f(
            cond_t const& __v,
            conds_t const&... __vs)
        {
            return __v or or_f(__vs...);
        }

          template<
            typename ... conds_t>
        using or_ = ibool_<or_f(conds_t::value...)>;


        constexpr bool 
        and_f()
        {
            return true;
        }

        constexpr bool
        and_f(
            bool const& __v)
        {
            return __v;
        }

        template<
            typename cond_t, 
            typename ... conds_t>
        constexpr bool
        and_f(
            cond_t const& __v,
            conds_t const&... __vs)
        {
            return __v and and_f(__vs...);
        }

       
        template<
            typename ... conds_t>
        using and_ = ibool_<and_f(conds_t::value...)>;


        constexpr bool
        not_f(
            bool const& __v)
        {
            return !__v;
        }

              
        template<
            typename cond_t>
        using not_ = ibool_<not_f(cond_t::value)>;

      

        




    


        namespace lazy
        {
            template<
                typename type1_t,
                typename type2_t>
            struct is_same :
                    false_ {};

            template<
                typename type_t>
            struct is_same<type_t, type_t> :
                    true_ {};




            template<
                typename base_t, 
                typename derived_t>
            struct is_base_of :
                    ibool_<__is_base_of(base_t, derived_t)> {}; 




            template<
                typename type_t>
            struct is_void :
                    __type<is_same<type_t, void>> {};




            template<
                typename type_t>
            struct is_null_ptr :
                    is_same<type_t, std::nullptr_t> {};




            template<
                typename type_t>
            struct is_integral:
                or_<is_same<type_t, bool>,
                    is_same<type_t, unsigned char>,
                    is_same<type_t, signed char>,
                    is_same<type_t, char16_t>,
                    is_same<type_t, char32_t>,
                    is_same<type_t, wchar_t>,
                    is_same<type_t, unsigned short>,
                    is_same<type_t, unsigned int>,
                    is_same<type_t, unsigned long>,
                    is_same<type_t, unsigned long long>,
                    is_same<type_t, short>,
                    is_same<type_t, int>,
                    is_same<type_t, long>,
                    is_same<type_t, long long>,
                    is_same<type_t, signed short>,
                    is_same<type_t, signed int>,
                    is_same<type_t, signed long>,
                    is_same<type_t, signed long long>> {};




            template<
                typename type_t>
            struct is_floating_point:
                    or_<is_same<type_t, float>,
                        is_same<type_t, double>,
                        is_same<type_t, long double>> {};




            template<
                typename type_t>
            struct is_array:
                    false_ {};

            template<
                typename type_t>
            struct is_array<type_t[]>:
                    true_ {};

            template<
                typename type_t,
                unsigned_t size_c>
            struct is_array<type_t[size_c]>:
                    true_{};




            template<
                typename type_t>
            struct is_enum:
                    ibool_<__is_enum(type_t)> {};




            template<
                typename type_t>
            struct is_union:
                    ibool_<__is_union(type_t)> {};




            template<
                typename type_t>
            struct is_class:
                    ibool_<__is_class(type_t)> {};




            template<
                typename type_t>
            struct is_empty:
                    ibool_<__is_empty(type_t)> {};




            template<
                typename type_t>
            struct is_function:
                    false_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...)>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...)&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...)&&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......)>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......)&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......)&&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...) const>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...) const&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...) const&&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......) const>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......) const&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......) const&&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...) volatile>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...) volatile&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...) volatile&&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......) volatile>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......) volatile&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......) volatile &&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...) const volatile>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...) const volatile&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t...) const volatile&&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......) const volatile>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......) const volatile&>:
                    true_ {};

            template<
                typename res_t,
                typename ... args_t>
            struct is_function<res_t(args_t......) const volatile &&>:
                    true_ {};




            template<
                typename tmp_t>
            struct is_pointer : false_ {};

            template<
                typename tmp_t>
            struct is_pointer<tmp_t*> : true_{};




            template<
                typename type_t>
            struct is_lvalue_reference:
                    false_ {};

            template<
                typename type_t>
            struct is_lvalue_reference<type_t&>:
                    true_ {};




            template<
                typename type_t>
            struct is_rvalue_reference:
                    false_ {};

            template<
                typename type_t>
            struct is_rvalue_reference<type_t&&>:
                    true_ {};




            template<
                typename type_t>
            struct is_member_object_pointer:
                    false_ {};

            template<
                typename type_t,
                typename class_t>
            struct is_member_object_pointer<type_t class_t::*>:
                    not_<is_function<type_t>> {};




            template<
                typename type_t>
            struct is_member_function_pointer:
                    false_ {};

            template<
                typename type_t,
                typename class_t>
            struct is_member_function_pointer<type_t class_t::*>:
                    is_function<type_t> {};




            template<
                typename type_t>
            struct is_member_pointer:
                    false_ {};

            template<
                typename type_t,
                typename class_t>
            struct is_member_pointer<type_t class_t::*>:
                    true_ {};




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




            template<
                typename type_t>
            struct is_reference:
                    or_<is_lvalue_reference<type_t>,
                        is_rvalue_reference<type_t>> {};



            template<
                typename type_t>
            using add_const = type_<type_t const>;




            template<
                typename type_t>
            using add_volatile = type_<type_t volatile>;




            template<
                typename type_t>
            using add_cv = type_<type_t const volatile>;




            template<
                typename type_t>
            using add_pointer = type_<type_t*>;




            template<
                typename type_t>
            using add_lvalue_reference = type_<type_t&>;




            template<
                typename type_t>
            using add_rvalue_reference = type_<type_t&&>;




            template<
                typename type_t>
            struct remove_const:
                    type_<type_t> {};

            template<
                typename type_t>
            struct remove_const<type_t const>:
                    type_<type_t> {};




            template<
                typename type_t>
            struct remove_volatile:
                    type_<type_t> {};

            template<
                typename type_t>
            struct remove_volatile<type_t volatile>:
                    type_<type_t> {};




            template<
                typename type_t>
            struct remove_pointer:
                    type_<type_t> {};

            template<
                typename type_t>
            struct remove_pointer<type_t *>:
                    type_<type_t> {};




            template<
                typename type_t>
            struct remove_reference:
                    type_<type_t> {};

            template<
                typename type_t>
            struct remove_reference<type_t &>:
                    type_<type_t> {};

            template<
                typename type_t>
            struct remove_reference<type_t &&>:
                    type_<type_t> {};
        }





#  define ATOM_IS_XXXX_F(name)                \
        template<                             \
            typename type_t>                 \
        constexpr bool name##_f(             \
                type_<type_t> const&)         \
        {                                     \
            return name<type_t>::value;          \
        }                                     \

        template<
            typename type1_t,
            typename type2_t>
        using is_same = __type<lazy::is_same<type1_t, type2_t>>;

        template<
            typename type1_t,
            typename type2_t>
        constexpr bool
        is_same_f(
            type_<type1_t> const&,
            type_<type2_t> const&)
        {
            return is_same<type1_t, type2_t>::value;
        }

        template<
            typename base_t, 
            typename derived_t>
        using is_base_of = __type<lazy::is_base_of<base_t, derived_t>>;

        template<
            typename base_t, 
            typename derived_t>
        constexpr bool 
        is_base_of_f(
            type_<base_t> const&,
            type_<derived_t> const&)
        {
            return is_base_of<base_t, derived_t>::value;
        }

        template<
            typename type_t>
        using is_void = __type<lazy::is_void<type_t>>;

        ATOM_IS_XXXX_F(is_void)

        template<
            typename type_t>
        using is_null_ptr = __type<lazy::is_null_ptr<type_t>>;

        ATOM_IS_XXXX_F(is_null_ptr)

        template<
            typename type_t>
        using is_integral = __type<lazy::is_integral<type_t>>;

        ATOM_IS_XXXX_F(is_integral)

        template<
            typename type_t>
        using is_floating_point = __type<lazy::is_floating_point<type_t>>;

        ATOM_IS_XXXX_F(is_floating_point)

        template<
            typename type_t>
        using is_array = __type<lazy::is_array<type_t>>;

        ATOM_IS_XXXX_F(is_array)

        template<
            typename type_t>
        using is_enum = __type<lazy::is_enum<type_t>>;

        ATOM_IS_XXXX_F(is_enum)

        template<
            typename type_t>
        using is_union = __type<lazy::is_union<type_t>>;

        ATOM_IS_XXXX_F(is_union)

        template<
            typename type_t>
        using is_class = __type<lazy::is_class<type_t>>;

        ATOM_IS_XXXX_F(is_class)

        template<
            typename type_t>
        using is_empty = __type<lazy::is_empty<type_t>>;

        ATOM_IS_XXXX_F(is_empty)

        template<
            typename type_t>
        using is_function = __type<lazy::is_function<type_t>>;

        ATOM_IS_XXXX_F(is_function)

        template<
            typename type_t>
        using is_pointer = __type<lazy::is_pointer<type_t>>;

        ATOM_IS_XXXX_F(is_pointer)

        template<
            typename type_t>
        using is_lvalue_reference = __type<lazy::is_lvalue_reference<type_t>>;

        ATOM_IS_XXXX_F(is_lvalue_reference)

        template<
            typename type_t>
        using is_rvalue_reference = __type<lazy::is_rvalue_reference<type_t>>;

        ATOM_IS_XXXX_F(is_rvalue_reference)

        template<
            typename type_t>
        using is_member_object_pointer = __type<lazy::is_member_object_pointer<type_t>>;

        ATOM_IS_XXXX_F(is_member_object_pointer)

        template<
            typename type_t>
        using is_member_function_pointer = __type<lazy::is_member_function_pointer<type_t>>;

        ATOM_IS_XXXX_F(is_member_function_pointer)

        template<
            typename type_t>
        using is_member_pointer = __type<lazy::is_member_pointer<type_t>>;

        ATOM_IS_XXXX_F(is_member_pointer)

        template<
            typename type_t>
        using is_arithmetic = __type<lazy::is_arithmetic<type_t>>;

        ATOM_IS_XXXX_F(is_arithmetic)

        template<
            typename type_t>
        using is_fundamental = __type<lazy::is_fundamental<type_t>>;

        ATOM_IS_XXXX_F(is_fundamental)

        template<
            typename type_t>
        using is_scalar = __type<lazy::is_scalar<type_t>>;

        ATOM_IS_XXXX_F(is_scalar)

        template<
            typename type_t>
        using is_object = __type<lazy::is_object<type_t>>;

        ATOM_IS_XXXX_F(is_object)

        template<
            typename type_t>
        using is_compound = __type<lazy::is_compound<type_t>>;

        ATOM_IS_XXXX_F(is_compound)

        template<
            typename type_t>
        using is_reference = __type<lazy::is_reference<type_t>>;

        ATOM_IS_XXXX_F(is_reference)




#  define ATOM_ADD_XXXX_F(name)                \
        template<                            \
            typename type_t>                \
        constexpr auto name##_f(            \
            type_<type_t> const&)            \
        {                                    \
            return type_<name<type_t>>{};    \
        }                                    \


        template<
            typename type_t>
        using add_const = __type<lazy::add_const<type_t>>;

        ATOM_ADD_XXXX_F(add_const)

        template<
            typename type_t>
        using add_volatile = __type<lazy::add_volatile<type_t>>;

        ATOM_ADD_XXXX_F(add_volatile)

        template<
            typename type_t>
        using add_cv = __type<lazy::add_cv<type_t>>;

        ATOM_ADD_XXXX_F(add_cv)

        template<
            typename type_t>
        using add_pointer = __type<lazy::add_pointer<type_t>>;

        ATOM_ADD_XXXX_F(add_pointer)

        template<
            typename type_t>
        using add_lvalue_reference = __type<lazy::add_lvalue_reference<type_t>>;

        ATOM_ADD_XXXX_F(add_lvalue_reference)

        template<
            typename type_t>
        using add_rvalue_reference = __type<lazy::add_rvalue_reference<type_t>>;

        ATOM_ADD_XXXX_F(add_rvalue_reference)


#  define ATOM_REMOVE_XXXX_F(name)            \
        template<                            \
            typename type_t>                \
        constexpr auto name##_f(            \
            type_<type_t> const&)            \
        {                                    \
            return type_<name<type_t>>{};    \
        }                                    \


        template<
            typename type_t>
        using remove_const = __type<lazy::remove_const<type_t>>;

        ATOM_REMOVE_XXXX_F(remove_const)

        template<
            typename type_t>
        using remove_volatile = __type<lazy::remove_volatile<type_t>>;

        ATOM_REMOVE_XXXX_F(remove_volatile)

        template<
            typename type_t>
        using remove_cv = remove_volatile<
                            remove_const<type_t>>;

        ATOM_REMOVE_XXXX_F(remove_cv)

        template<
            typename type_t>
        using remove_pointer = __type<lazy::remove_pointer<type_t>>;

        ATOM_REMOVE_XXXX_F(remove_pointer)

        template<
            typename type_t>
        using remove_reference = __type<lazy::remove_reference<type_t>>;

        ATOM_REMOVE_XXXX_F(remove_reference)

        template<
            typename type_t>
        using remove_all = remove_cv<
                             remove_pointer<
                               remove_reference<type_t>>>;

        template<
            typename type_t>
        using decay = remove_cv<
                        remove_reference<type_t>>;

        ATOM_REMOVE_XXXX_F(remove_all)



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


#  define ATOM_USING_MEMBER(name)                           \
        [](auto&& _t)                                       \
        -> typename meta::remove_all<decltype(_t)>::name {} \


#  define ATOM_STATIC_ATTRIBUTE_MEMBER(name)           \
        [](auto&& _t)                                  \
        -> decltype(remove_all<decltype(_t)>::name) {} \


        constexpr auto has_type       = is_valid(ATOM_USING_MEMBER(type));
        constexpr auto has_value_type = is_valid(ATOM_USING_MEMBER(value_type));

        constexpr auto has_static_value = is_valid(ATOM_STATIC_ATTRIBUTE_MEMBER(value));


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
        using enable_if = lazy::enable_if<bool_c, type_t>;
    }
}




#endif /* ATOM_META_HPP_ */
