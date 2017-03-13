#ifndef __THODD_CONTAINER_DSL_HPP__
#  define __THODD_CONTAINER_DSL_HPP__

#  include <thodd/dsl.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/container/functional.hpp>

namespace thodd
{
    namespace contdsl
    {
        namespace detail
        {
            template<
                typename getter_t>
            struct with_node
            {
                getter_t get;
            };

            template<
                typename algo_t>
            struct foreach_node
            {
                algo_t algo;
            };

            template<
                typename algo_t>
            struct foreach_iter_node
            {
                algo_t algo;
            };

            template<
                typename cond_t>
            struct where_node
            {
                cond_t cond;
            };
            
            template<
                typename order_t>
            struct sort_node
            {
                order_t order;
            };

            template<
                typename limit_t>
            struct limit_node
            {
                limit_t limit;
            };

            template<
                typename first_t>
            struct first_node
            {
                first_t first;
            };
        }

        constexpr auto $item = $0;

        template<
            typename getter_t>
        constexpr auto
        with(
            getter_t&& __get)
        {
            return  make_node<detail::with_node>(perfect<getter_t>(__get));
        }
      
        template<
            typename algo_t>
        constexpr auto
        foreach(
            algo_t&& __algo)
        {
            return  make_node<detail::foreach_node>(perfect<algo_t>(__algo));
        }

        template<
            typename algo_t>
        constexpr auto
        foreach_iter(
            algo_t&& __algo)
        {
            return  make_node<detail::foreach_iter_node>(perfect<algo_t>(__algo));
        }
        
        template<
            typename cond_t>
        constexpr auto
        where(
            cond_t&& __cond)
        {
            return  make_node<detail::where_node>(perfect<cond_t>(__cond));
        }

        template<
            typename val_t>
        constexpr auto
        update(
            val_t&& __val)
        {
            return make_node<detail::foreach_node>($item = perfect<val_t>(__val));
        }

        template<
            typename order_t>
        constexpr auto
        sort(
            order_t&& __order)
        {
            return  make_node<detail::sort_node>(perfect<order_t>(__order));
        }


        template<
            typename view_t>
        constexpr auto
        select(
            view_t&& __view)
        {
            return  make_node<detail::foreach_node>(bind(push_back, __view, $item));    
        }


        template<
            typename view_t>
        constexpr auto
        transfer(
            view_t&& __view)
        {
            return  make_node<detail::foreach_node>(bind(move_back, __view, $item));    
        }


        template<
            typename ref_t>
        constexpr auto
        count(
            ref_t&& __ref)
        {
            return  make_node<detail::foreach_node>(++perfect<ref_t>(__ref));
        }

        template<
            typename limit_t>
        constexpr auto 
        limit(
            limit_t&& __limit)
        {
            return  make_node<detail::limit_node>(__limit);
        }

        template<
            typename first_t>
        constexpr auto 
        first(
            first_t&& __first)
        {
            return  make_node<detail::first_node>(__first);
        }



        struct asc_order
        {
            template<
                typename left_t, 
                typename right_t>
            operator() (
                left_t&& __left, 
                right_t&& __right) const
            {
                return __left < __right;
            }
        };

        extern constexpr asc_order asc{};

        struct desc_order
        {
            template<
                typename left_t, 
                typename right_t>
            operator() (
                left_t&& __left, 
                right_t&& __right) const
            {
                return __left > __right;
            }
        };

        extern constexpr desc_order desc{};


        template<
            typename dsl_expression_t>
        struct query;


        template<
            typename func_t, 
            typename algorithm_t>
        using with_foreach = 
                dsl_expression<
                    detail::with_node<func_t>, 
                    detail::foreach_node<algorithm_t>>; 

        template<
            typename func_t, 
            typename algorithm_t>
        struct query<
                with_foreach<
                        func_t, 
                        algorithm_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator()(
                with_foreach<func_t, algorithm_t> const& __dsl,
                args_t&&... __args) const
            {
                auto&& __source = get<0>(__dsl).get(perfect<args_t>(__args)...);
                auto&& __algo = get<1>(__dsl).algo;
                
                for(auto&& __item : __source)
                    __algo(__item, perfect<args_t>(__args)...);          
            }
        };


        template<
            typename func_t, 
            typename algorithm_t, 
            typename limit_t>
        using with_foreach_limit = 
                dsl_expression<
                    detail::with_node<func_t>, 
                    detail::foreach_node<algorithm_t>,
                    detail::limit_node<limit_t>>; 

        namespace detail
        {
            struct dsl_cond_algo_impl
            {
                template<
                    typename dsl_t, 
                    typename item_t, 
                    typename ... args_t>
                inline void
                operator()(
                    dsl_t const& __dsl, 
                    item_t&& __item, 
                    args_t&&... __args) const
                {
                    auto&& __cond = get<2>(__dsl);
                    auto&& __algo = get<1>(__dsl);

                    if(__cond(perfect<item_t>(__item),
                                perfect<args_t>(__args)...))
                        __algo(perfect<item_t>(__item), 
                                perfect<args_t>(__args)...);
                }
            };

            extern constexpr dsl_cond_algo_impl dsl_cond_algo{};
        }

        template<
            typename func_t, 
            typename algorithm_t, 
            typename limit_t>
        struct query<
                with_foreach_limit<
                    func_t, 
                    algorithm_t, 
                    limit_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator()(
                with_foreach_limit<func_t, algorithm_t, limit_t> const& __dsl,
                args_t&&... __args) const
            {
                auto&& __source = get<0>(__dsl).get(perfect<args_t>(__args)...);
                auto&& __algo = get<1>(__dsl).algo;
                auto&& __limit = get<2>(__dsl).limit(perfect<args_t>(__args)...);
                size_t __cpt{0u};

                for(auto&& __item : __source)
                {
                    __algo(__item, perfect<args_t>(__args)...);          
                    ++__cpt;

                    if(__cpt >= __limit)
                        break;
                }
            }
        };

        
        template<
            typename getter_t, 
            typename algorithm_t, 
            typename cond_t>
        using with_foreach_where = 
                dsl_expression<
                    detail::with_node<getter_t>, 
                    detail::foreach_node<algorithm_t>, 
                    detail::where_node<cond_t>>;

        template<
            typename getter_t, 
            typename algorithm_t, 
            typename cond_t>
        struct query<with_foreach_where<
                        getter_t, 
                        algorithm_t, 
                        cond_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator()(
                with_foreach_where<getter_t, algorithm_t, cond_t> const& __dsl,
                args_t&&... __args) const
            {
                auto const __algo = bind(detail::dsl_cond_algo, 
                                         ref(__dsl), $0, $1);
                            
                go<query>(
                    with(get<0>(__dsl).get) 
                    > foreach(__algo), 
                    perfect<args_t>(__args)...);
            }
        };


        template<
            typename getter_t, 
            typename algorithm_t, 
            typename cond_t, 
            typename limit_t>
        using with_foreach_where_limit = 
                dsl_expression<
                    detail::with_node<getter_t>, 
                    detail::foreach_node<algorithm_t>, 
                    detail::where_node<cond_t>, 
                    detail::limit_node<limit_t>>;

        template<
            typename getter_t, 
            typename algorithm_t, 
            typename cond_t, 
            typename limit_t>
        struct query<with_foreach_where_limit<
                        getter_t, 
                        algorithm_t, 
                        cond_t, 
                        limit_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator()(
                with_foreach_where_limit<
                    getter_t, 
                    algorithm_t, 
                    cond_t, 
                    limit_t> const& __dsl,
                args_t&&... __args) const
            {
                auto const __algo = bind(detail::dsl_cond_algo, 
                                         ref(__dsl), $0, $1);
                            
                go<query>(
                    with(get<0>(__dsl).get) 
                    > foreach(__algo) 
                    > limit(get<3>(__dsl).limit), 
                    perfect<args_t>(__args)...);
            }
        };








        template<
            typename func_t, 
            typename algorithm_t>
        using with_foreach_iter = 
                dsl_expression<
                    detail::with_node<func_t>, 
                    detail::foreach_iter_node<algorithm_t>>; 

        template<
            typename func_t, 
            typename algorithm_t>
        struct query<
                with_foreach_iter<
                        func_t, 
                        algorithm_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator()(
                with_foreach_iter<func_t, algorithm_t> const& __dsl,
                args_t&&... __args) const
            {
                auto&& __source = get<0>(__dsl).get(perfect<args_t>(__args)...);
                auto&& __algo = get<1>(__dsl).algo;
                auto& __begin = __source.begin();
                auto const& __end = __source.end();

                while(__begin != __end)
                {
                    __algo(__begin, perfect<args_t>(__args)...);          
                    ++__begin;
                }
            }
        };


        template<
            typename func_t, 
            typename algorithm_t, 
            typename limit_t>
        using with_foreach_iter_limit = 
                dsl_expression<
                    detail::with_node<func_t>, 
                    detail::foreach_iter_node<algorithm_t>,
                    detail::limit_node<limit_t>>; 

        template<
            typename func_t, 
            typename algorithm_t, 
            typename limit_t>
        struct query<with_foreach_iter_limit<
                        func_t, 
                        algorithm_t, 
                        limit_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator()(
                with_foreach_iter_limit<
                    func_t, 
                    algorithm_t, 
                    limit_t> const& __dsl,
                args_t&&... __args) const
            {
                auto&& __source = get<0>(__dsl).get(perfect<args_t>(__args)...);
                auto&& __algo = get<1>(__dsl).algo;
                auto&& __limit = get<2>(__dsl).limit(perfect<args_t>(__args)...);
                size_t __cpt{0u};

                auto& __begin = __source.begin();
                auto const& __end = __source.end();

                while(__begin != __end)
                {
                    __algo(__begin, perfect<args_t>(__args)...);          
                    ++__cpt;

                    if(__cpt >= __limit)
                        break;

                    ++__begin;
                }
            }
        };

        
        template<
            typename getter_t, 
            typename algorithm_t, 
            typename cond_t>
        using with_foreach_iter_where = 
                dsl_expression<
                    detail::with_node<getter_t>, 
                    detail::foreach_iter_node<algorithm_t>, 
                    detail::where_node<cond_t>>;

        template<
            typename getter_t, 
            typename algorithm_t, 
            typename cond_t>
        struct query<with_foreach_iter_where<
                        getter_t, 
                        algorithm_t, 
                        cond_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator()(
                with_foreach_iter_where<
                    getter_t, 
                    algorithm_t, 
                    cond_t> const& __dsl,
                args_t&&... __args) const
            {
                auto const __algo = bind(detail::dsl_cond_algo, 
                                         ref(__dsl), $0, $1);
                            
                go<query>(
                    with(get<0>(__dsl).get) 
                    > foreach_iter(__algo), 
                    perfect<args_t>(__args)...);
            }
        };


        template<
            typename getter_t, 
            typename algorithm_t, 
            typename cond_t, 
            typename limit_t>
        using with_foreach_iter_where_limit = 
                dsl_expression<
                    detail::with_node<getter_t>, 
                    detail::foreach_iter_node<algorithm_t>, 
                    detail::where_node<cond_t>, 
                    detail::limit_node<limit_t>>;

        template<
            typename getter_t, 
            typename algorithm_t, 
            typename cond_t, 
            typename limit_t>
        struct query<with_foreach_iter_where_limit<
                        getter_t, 
                        algorithm_t, 
                        cond_t, 
                        limit_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator()(
                with_foreach_iter_where_limit<
                    getter_t, 
                    algorithm_t, 
                    cond_t, 
                    limit_t> const& __dsl,
                args_t&&... __args) const
            {
                auto const __algo = bind(detail::dsl_cond_algo, 
                                         ref(__dsl), $0, $1);
                            
                go<query>(
                    with(get<0>(__dsl).get) 
                    > foreach_iter(__algo) 
                    > limit(get<3>(__dsl).limit), 
                    perfect<args_t>(__args)...);
            }
        };

        namespace detail
        {
            struct sort_view
            {
                template<
                    typename view_t, 
                    typename order_t>
                inline auto
                operator() (
                    view_t& __container, 
                    order_t const& __order) const
                {
                    auto&& __current  = __container.begin();
                    auto const& __end = __container.end();

                    while(__current != __end)
                    {
                        auto __after = __current;
                        ++__after;

                        while(__after != __end)
                        {
                            if(__order(*__after, *__current))
                            {
                                auto __tmp = rvalue(*__after);
                                *__after   = rvalue(*__current);
                                *__current = rvalue(__tmp);
                            }

                            ++__after;
                        }

                        ++__current;
                    }
                }
            };
        }

        template<
            typename getter_t, 
            typename order_t>
        using with_sort = 
                dsl_expression<
                    detail::with_node<getter_t>, 
                    detail::sort_node<order_t>>;

        template<
            typename getter_t,
            typename order_t>
        struct query<with_sort<
                        getter_t, 
                        order_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator()(
                with_sort<getter_t, order_t> const& __dsl,
                args_t&&... __args) const
            {
                constexpr detail::sort_view __sort;
                auto&& __getter = get<0>(__dsl).get;
                __sort(__getter(perfect<args_t>(__args)...), 
                       get<1>(__dsl).order);
            }
        };

        template<
            typename getter_t,
            typename first_t>
        using with_first = 
                dsl_expression<
                    detail::with_node<getter_t>, 
                    detail::first_node<first_t>>;
        
        template<
            typename getter_t, 
            typename first_t>
        struct query<with_first<getter_t, first_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator() (
                with_first<getter_t, first_t> const& __cdsl,
                args_t&&... __args) const
            {
                auto&& __source = get<0>(__cdsl).get(perfect<args_t>(__args)...);
                auto&& __first = get<1>(__cdsl).first(perfect<args_t>(__args)...);

                __first = __source.begin();
            }
        };

        template<
            typename getter_t,
            typename first_t, 
            typename cond_t>
        using with_first_where = 
                dsl_expression<
                    detail::with_node<getter_t>, 
                    detail::first_node<first_t>, 
                    detail::where_node<cond_t>>;
        
        template<
            typename getter_t, 
            typename first_t, 
            typename cond_t>
        struct query<with_first_where<getter_t, first_t, cond_t>>
        {
            template<
                typename ... args_t>
            inline auto
            operator() (
                with_first_where<getter_t, first_t, cond_t> const& __cdsl,
                args_t&&... __args) const
            {
                auto&& __source = get<0>(__cdsl).get(perfect<args_t>(__args)...);
                auto&& __first = get<1>(__cdsl).first(perfect<args_t>(__args)...);
                auto&& __cond = get<2>(__cdsl).cond;
                
                auto const& __end = __source.end();
                auto __begin = __source.begin();

                while(__begin != __end)
                {
                    if(__cond(*__begin, perfect<args_t>(__args)...))
                    {
                        __first = __begin;
                        return;
                    }
                    
                    ++__begin;
                }
                __first = __end;
            }
        };
    }

    namespace contdsl
    {
        extern constexpr auto copy = with($0) > select($2);
        extern constexpr auto copy_if = with($0) > select($2) > where($3);
    }
}



#endif