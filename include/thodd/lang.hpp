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
            typename type_t>
        using __target = typename type_t::target;

        namespace matcher
        {
            template<
                typename algo_t>
            struct matcher
            {
                algo_t algo;

                inline auto
                operator() (
                    auto& __cursor, 
                    auto const& __end) const
                {
                    return algo(__cursor, __end);
                }
            };


            constexpr auto
            make_matcher(
                auto&& __algo)
            {
                using algo_t     = decltype(__algo);
                using algo_dec_t = meta::decay<algo_t>;

                return matcher<algo_dec_t>{perfect<algo_t>(__algo)};
            }

            
        
        
            template<
                typename ... algorithms_t>
            struct alternative
            {
                tuple<algorithms_t...> algos;

                template<
                    size_t ... indexes_c>
                inline auto
                operator()(
                    auto& __cursor, 
                    auto const& __end,
                    indexes<indexes_c...> const&) const 
                -> decltype(auto)
                {
                    auto __one_matched = false;
                    repeat{(__one_matched = __one_matched || get<indexes_c>(algos)(__cursor, __end), 0)...};
                    return __one_matched;
                }

                template<
                    typename iterator_t>
                inline auto 
                operator() (
                    iterator_t& __cursor, 
                    iterator_t const& __end) const
                -> decltype(auto)
                {
                    return (*this)(__cursor, __end, make_indexes<sizeof...(algorithms_t)>{});  
                }
            };


            template<
                typename lalgo_t, 
                typename ralgo_t>
            constexpr auto
            operator | (
                matcher<lalgo_t> const& __left, 
                matcher<ralgo_t> const& __right)
            -> decltype(auto)
            {
                using left_or_right_t = alternative<
                                            meta::decay<lalgo_t>, 
                                            meta::decay<ralgo_t>>;

                return make_matcher(
                        left_or_right_t{
                            make_tuple(__left.algo, 
                                       __right.algo)});
            }

            
            template<
                typename ... l_algorithms_t, 
                typename ralgo_t>
            constexpr auto
            operator | (
                matcher<alternative<l_algorithms_t...>> const& __left, 
                matcher<ralgo_t> const& __right)
            -> decltype(auto)
            {
                using lefts_or_right_t = alternative<
                                            meta::decay<l_algorithms_t>..., 
                                            meta::decay<ralgo_t>>;

                return make_matcher(lefts_or_right_t{__left.algo.algos + __right.algo});
            }


            template<
                typename lalgo_t, 
                typename ... r_algorithms_t>
            constexpr auto
            operator | (
                matcher<lalgo_t> const& __left, 
                matcher<alternative<r_algorithms_t...>> const& __right)
            -> decltype(auto)
            {
                using left_or_rights_t = alternative<meta::decay<lalgo_t>, meta::decay<r_algorithms_t>...>;

                return make_matcher(left_or_rights_t{__left.algo + __right.algo.algos});
            }

            
            template<
                typename ... l_algorithms_t, 
                typename ... r_algorithms_t>
            constexpr auto
            operator | (
                matcher<alternative<l_algorithms_t...>> const& __left, 
                matcher<alternative<r_algorithms_t...>> const& __right)
            -> decltype(auto)
            {
                using lefts_or_rights_t = alternative<meta::decay<l_algorithms_t>..., meta::decay<r_algorithms_t>...>;

                return make_matcher(lefts_or_rights_t{__left.algo.algos + __right.algo.algos});
            }




            template<
                typename algo_t>
            struct some
            {
                algo_t algo;

                size_t min_c{0};
                size_t max_c{1};

                constexpr auto 
                operator() (
                    size_t __min, 
                    size_t __max) const
                {
                    return make_matcher(some<algo_t> {algo, __min, __max});
                }


                constexpr auto 
                operator() (
                    size_t __strict) const
                {
                    return make_matcher(some<algo_t> {algo, __strict, __strict});
                }


                inline auto 
                operator() (
                    auto& __cursor, 
                    auto const& __end) const
                -> decltype(auto)
                {
                    auto __cpt = 0u;

                    while(__cursor != __end 
                      && algo(__cursor, __end))
                        ++__cpt;

                    return min_c <= __cpt && __cpt <= max_c; 
                }
            };

            template<
                typename ralgo_t>
            constexpr auto 
            operator ~ (
                matcher<ralgo_t> const& __right)
            -> decltype(auto)
            {
                using some_t = some<meta::decay<ralgo_t>>;

                return some_t{__right.algo};
            }

            template<
                typename ralgo_t>
            constexpr auto
            operator * (
                matcher<ralgo_t> const& __right)
            -> decltype(auto)
            {
                return (~__right)(0, infinity);
            }


            template<
                typename ralgo_t>
            constexpr auto
            operator + (
                matcher<ralgo_t> const& __right)
            -> decltype(auto)
            {
                return (~__right)(1, infinity);
            }

           



            template<
                typename ... algorithms_t>
            struct follow
            {
                tuple<algorithms_t...> algos;


                template<
                    typename iterator_t, 
                    size_t ... indexes_c>
                inline auto 
                operator() (
                    iterator_t& __cursor, 
                    iterator_t const& __end, 
                    indexes<indexes_c...> const&) const
                -> decltype(auto)
                {
                    auto __all_matched = true;
                    repeat{(__all_matched = __all_matched && get<indexes_c>(algos)(__cursor, __end), 0)...};
                    return __all_matched;
                }


                template<
                    typename iterator_t>
                inline auto 
                operator()(
                    iterator_t& __cursor, 
                    iterator_t const& __end) const
                -> decltype(auto)
                {
                    return (*this)(__cursor, __end, make_indexes<sizeof...(algorithms_t)>{});
                }
            };


            template<
                typename lalgo_t, 
                typename ralgo_t>
            constexpr auto
            operator >> (
                matcher<lalgo_t> const& __left,
                matcher<ralgo_t> const& __right)
            {
                using follow_t = follow<meta::decay<lalgo_t>, meta::decay<ralgo_t>>;

                return make_matcher(follow_t{make_tuple(__left.algo, __right.algo)});
            }



            template<
                typename ... l_algorithms_t, 
                typename ralgo_t>
            constexpr auto
            operator >> (
                matcher<follow<l_algorithms_t...>> const& __left,
                matcher<ralgo_t> const& __right)
            {
                using follow_t = follow<meta::decay<l_algorithms_t>..., meta::decay<ralgo_t>>;

                return make_matcher(follow_t{__left.algo.algos + __right.algo});
            }

            
            template<
                typename lalgo_t, 
                typename ... r_algorithms_t>
            constexpr auto
            operator >> (
                matcher<lalgo_t> const& __left,
                matcher<follow<r_algorithms_t...>> const& __right)
            {
                using follow_t = follow<meta::decay<lalgo_t>, meta::decay<r_algorithms_t>...>;

                return make_matcher(follow_t{__left.algo + __right.algo.algos});
            }


            template<
                typename ... l_algorithms_t, 
                typename ... r_algorithms_t>
            constexpr auto
            operator >> (
                matcher<follow<l_algorithms_t...>> const& __left,
                matcher<follow<r_algorithms_t...>> const& __right)
            {
                using follow_t = follow<meta::decay<l_algorithms_t>..., meta::decay<r_algorithms_t>...>;

                return make_matcher(follow_t{__left.algo.algos + __right.algo.algos});
            }
        }



        namespace caster
        {  
            /// # struct caster
            /// 
            /// Un caster permet d'encapsuler un 
            /// algorithme de transformation ainsi
            /// que le type cible voulu. Un même 
            /// algorithme peut être valable pour 
            /// plusieurs types cibles.
            ///
            /// # typename algo_t  algorithme encaspulé
            /// # typename target_t     type cible de l'algorithme
            template<
                typename algo_t, 
                typename target_t, 
                typename reactor_t = decltype(nothing)>
            struct caster
            {
                using target = target_t;

                algo_t algo;
                reactor_t react;

                template<
                    typename iterator_t>
                inline auto
                operator() (
                    iterator_t& __cursor, 
                    iterator_t const& __end, 
                    target_t& __tgt) const
                {
                    auto&& __res = algo(__cursor, __end, __tgt);
                    react(__cursor, __end, __tgt, __res);
                    return __res;
                }


                target attr() const
                {
                    return {};
                }

                template<
                    typename oreactor_t>
                constexpr auto
                operator[] (
                    oreactor_t const& __react) const
                {
                    return caster<algo_t, 
                                  target_t, 
                                  meta::decay<oreactor_t>>{algo, __react};
                }
            };


            template<
                typename target_t>
            constexpr auto 
            make_caster(
               auto&& __algo)
            {
                using algo_t     = decltype(__algo);
                using algo_dec_t = meta::decay<algo_t>;

                return 
                    caster<algo_dec_t, target_t>
                    {perfect<algo_t>(__algo)};
            }

        
            template<
                typename ... casters_t>
            struct alternative
            {
                tuple<casters_t...> casters;
                
                using target = variant<__target<casters_t>...>;

                template<
                    size_t index_c>
                using current = meta::at<index_c, target>;

                template<
                    typename iterator_t,
                    typename target_t,  
                    size_t ... indexes_c>
                inline auto
                operator()(
                    iterator_t& __cursor, 
                    iterator_t const& __end,
                    target_t& __tgt,
                    indexes<indexes_c...> const&) const 
                -> decltype(auto)
                {
                    auto __one_matched = false;
                    auto __save = __cursor;
                    
                    repeat{(
                        (__cursor = !__one_matched ? __save : __cursor), 
                        __one_matched = __one_matched || (__tgt = current<indexes_c>{}, 
                                                          get<indexes_c>(casters)(__cursor, __end, static_cast<current<indexes_c>&>(__tgt))), 0)...};
                    return __one_matched;
                }


                template<
                    typename iterator_t, 
                    typename target_t>
                inline auto 
                operator() (
                    iterator_t& __cursor, 
                    iterator_t const& __end, 
                    target_t& __tgt) const
                {                    
                    return (*this)(__cursor, __end, __tgt, 
                                   make_indexes<sizeof...(casters_t)>{});  
                }
            };


            template<
                typename ... lparams_t,
                typename ... rparams_t>
            constexpr auto
            operator | (
                caster<lparams_t...> const& __left, 
                caster<rparams_t...> const& __right)
            {
                using left_or_right_t = alternative<caster<lparams_t...>, caster<rparams_t...>>;
                
                using targets_t = __target<left_or_right_t>;
                
                return 
                    make_caster<targets_t>(
                        left_or_right_t{make_tuple(__left, __right)});
            }

            
            template<
                typename ... lcasters_t,
                typename ... rparams_t>
            constexpr auto
            operator | (
                caster<alternative<lcasters_t...>, __target<alternative<lcasters_t...>>> const& __left, 
                caster<rparams_t...> const& __right)
            {
                using lefts_or_right_t = alternative<lcasters_t..., caster<rparams_t...>>;
                using target_t = __target<lefts_or_right_t>;

                return 
                    make_caster<target_t>(
                        lefts_or_right_t{__left.algo.casters + __right});
            }


            template<
                typename ... lparams_t,
                typename ... rcasters_t>
            constexpr auto
            operator | (
                caster<lparams_t...> const& __left, 
                caster<alternative<rcasters_t...>, __target<alternative<rcasters_t...>>> const& __right)
            {
                using left_or_rights_t = alternative<caster<lparams_t...>, rcasters_t...>;
                using target_t = __target<left_or_rights_t>;

                return 
                    make_caster<target_t>(
                        left_or_rights_t{__left + __right.algo.algos});
            }

            
            template<
                typename ... lcasters_t, 
                typename ... rcasters_t>
            constexpr auto
            operator | (
                caster<alternative<lcasters_t...>, __target<alternative<rcasters_t...>>> const& __left, 
                caster<alternative<rcasters_t...>, __target<alternative<rcasters_t...>>> const& __right)
            -> decltype(auto)
            {
                using lefts_or_rights_t = alternative<lcasters_t..., rcasters_t...>;
                using target_t = __target<lefts_or_rights_t>;

                return 
                    make_caster<target_t>(
                        lefts_or_rights_t{__left.algo.casters + __right.algo.casters});
            }



            template<
                typename caster_t>
            struct some
            {
                caster_t caster;
                size_t min_c{0}, 
                       max_c{1};

                using target = list<__target<caster_t>>;

                constexpr auto 
                operator() (
                    size_t __min, 
                    size_t __max) const
                {
                    return 
                        make_caster<target>(
                            some<caster_t>{caster, __min, __max});
                }

                
                constexpr auto 
                operator() (
                    size_t __strict) const
                {
                    return 
                        make_caster<target>(
                            some<caster_t>{caster, __strict, __strict});
                }


                template<
                    typename iterator_t>
                inline auto 
                operator() (
                    iterator_t& __cursor, 
                    iterator_t const& __end, 
                    target& __tgt) const
                {
                    while(__cursor != __end 
                       && __tgt.size() <= max_c)
                    {
                        __target<caster_t> __tmp;
                        
                        if(caster(__cursor, __end, __tmp))
                            __tgt.push_at(__tmp, __tgt.end());
                        else 
                            break;
                    }

                    return min_c <= __tgt.size() && __tgt.size() <= max_c; 
                }
            };

            template<
                typename ... rparams_t>
            constexpr auto 
            operator ~ (
                caster<rparams_t...> const& __right)
            {
                return some<caster<rparams_t...>>{__right};
            }

            
            template<
                typename ... rparams_t>
            constexpr auto
            operator * (
                caster<rparams_t...> const& __right)
            {
                return (~__right)(0, infinity);
            }


            template<
                typename ... rparams_t>
            constexpr auto
            operator + (
                caster<rparams_t...> const& __right)
            {
                return (~__right)(1, infinity);
            }



            template<
                typename ... casters_t>
            struct follow
            {
                using target = tuple<__target<casters_t>...>;
                   
                tuple<casters_t...> casters;

                template<
                    size_t index_c,
                    typename iterator_t>
                inline auto 
                step (
                    iterator_t& __cursor, 
                    iterator_t const& __end,
                    target& __tgt) const
                -> decltype(auto)
                {
                    return get<index_c>(casters)(__cursor, __end, get<index_c>(__tgt));
                }

                template<
                    typename iterator_t, 
                    size_t ... indexes_c>
                inline auto 
                operator() (
                    iterator_t& __cursor, 
                    iterator_t const& __end,
                    target& __tgt, 
                    indexes<indexes_c...> const&) const
                -> decltype(auto)
                {
                    auto __all_matched = true;
                    repeat{(__all_matched = __all_matched && step<indexes_c>(__cursor, __end, __tgt), 0)...};
                    return __all_matched;
                }


                template<
                    typename iterator_t>
                inline auto 
                operator()(
                    iterator_t& __cursor, 
                    iterator_t const& __end, 
                    target& __tgt) const
                -> decltype(auto)
                {
                    return (*this)(__cursor, __end, __tgt, 
                                   make_indexes<sizeof...(casters_t)>{});
                }
            };


            template<
                typename ... lparams_t,
                typename ... rparams_t>
            constexpr auto
            operator >> (
                caster<lparams_t...> const& __left,
                caster<rparams_t...> const& __right)
            {
                using follow_t = 
                    follow<
                        caster<lparams_t...>, 
                        caster<rparams_t...>>;

                using target_t = __target<follow_t>;

                return 
                    make_caster<target_t>(
                        follow_t{make_tuple(__left, __right)});
            }



            template<
                typename ... lcasters_t,
                typename ... rparams_t>
            constexpr auto
            operator >> (
                caster<follow<lcasters_t...>, __target<follow<lcasters_t...>>> const& __left,
                caster<rparams_t...> const& __right)
            {
                using follow_t = follow<lcasters_t..., caster<rparams_t...>>;
                using target_t = __target<follow_t>;

                return 
                    make_caster<target_t>(
                        follow_t{__left.algo.casters + __right});
            }

            

            template<
                typename ... lparams_t,
                typename ... rcasters_t>
            constexpr auto
            operator >> (
                caster<lparams_t...> const& __left, 
                caster<follow<rcasters_t...>, __target<follow<rcasters_t...>>> const& __right)
            {
                using follow_t = follow<caster<lparams_t...>, rcasters_t...>;
                using target_t = __target<follow_t>;

                return 
                    make_caster<target_t>(
                        follow_t{__right + __left.algo.casters});
            }


            template<
                typename ... lcasters_t,
                typename ... rcasters_t>
            constexpr auto
            operator >> (
                caster<follow<lcasters_t...>, __target<follow<lcasters_t...>>> const& __left,
                caster<follow<rcasters_t...>, __target<follow<rcasters_t...>>> const& __right)
            {
                using follow_t = follow<lcasters_t..., rcasters_t...>;
                using target_t = __target<follow_t>;

                return 
                    make_caster<target_t>(
                        follow_t{__left.algo.casters + __right.algo.casters});
            }
        }


        namespace parser
        {
            template<
                typename matcher_t, 
                typename caster_t>
            struct parser
            {
                matcher_t matcher;
                caster_t caster;

                using target = __target<caster_t>;

                template<
                    typename iterator_t>
                inline auto
                operator()(
                    iterator_t& __cursor, 
                    iterator_t const& __end) const
                -> decltype(auto)
                {   
                    return matcher(__cursor, __end);
                }

                template<
                    typename iterator_t>
                inline auto
                operator()(
                    iterator_t& __cursor, 
                    iterator_t const& __end, 
                    target& __tgt) const
                -> decltype(auto)
                {
                    return caster(__cursor, __end, __tgt);
                }

                target attr() const
                {
                    return {};
                }

                template<
                    typename oreactor_t>
                constexpr auto
                operator [] (
                    oreactor_t const& __react) const
                {
                    return parser<matcher_t, 
                                  meta::decay<decltype(caster[__react])>> {matcher, caster[__react]};
                }
            };           
        }

        namespace matcher
        {
            template<
                typename ... mparams_t, 
                typename ... cparams_t>
            constexpr auto 
            operator && (
                matcher<mparams_t...> const& __matcher, 
                caster::caster<cparams_t...> const& __caster)
            -> parser::parser<matcher<mparams_t...>, caster::caster<cparams_t...>>
            {
                return {__matcher, __caster};
            }
        }

        namespace parser
        {
           template<
                typename ... lparams_t, 
                typename ... rparams_t>
            constexpr auto
            operator | (
                parser<lparams_t...> const& __left, 
                parser<rparams_t...> const& __right)
            {
                return (__left.matcher | __right.matcher) 
                    && (__left.caster | __right.caster);
            }


            template<
                typename ... lparams_t, 
                typename ... rparams_t>
            constexpr auto
            operator >> (
                parser<lparams_t...> const& __left, 
                parser<rparams_t...> const& __right)
            {
                return (__left.matcher >> __right.matcher) 
                    && (__left.caster >> __right.caster);
            }


            template<
                typename matcher_t, 
                typename caster_t>
            struct some_parser
            {
                matcher_t matcher;
                caster_t caster;

                
                constexpr auto
                operator()(
                    size_t __min, 
                    size_t __max) const
                {
                    return (~matcher)(__min, __max) 
                        && (~caster)(__min, __max); 
                }

                constexpr auto
                operator()(
                    size_t __strict) const
                {
                    return (~matcher)(__strict, __strict) 
                        && (~caster)(__strict, __strict); 
                }
            };


            template<
                typename ... rparams_t>
            constexpr auto
            operator ~ (
                parser<rparams_t...> const& __right)
            {
                return some_parser<rparams_t...>{__right.matcher, __right.caster};
            }


             template<
                typename ... rparams_t>
            constexpr auto
            operator + (
                parser<rparams_t...> const& __right)
            {
                return (~__right)(1, infinity);
            }

             template<
                typename ... rparams_t>
            constexpr auto
            operator * (
                parser<rparams_t...> const& __right)
            {
                return (~__right)(0, infinity);
            }
        }



        
        template<
            typename ... params_t, 
            typename iterator_t>
        inline auto
        matches(
            parser::parser<params_t...> const& __parser,
            iterator_t& __cursor,
            iterator_t const& __end)
        -> decltype(auto)
        {
            return __parser(__cursor, __end);
        }

        
        template<
            typename ... params_t, 
            typename iterator_t>
        inline auto
        matches(
            matcher::matcher<params_t...> const& __matcher,
            iterator_t& __cursor,
            iterator_t const& __end)
        -> decltype(auto)
        {
            return __matcher(__cursor, __end);
        }

        template<
            typename ... params_t, 
            typename stream_t>
        inline auto
        matches(
            parser::parser<params_t...> const& __parser,
            stream_t const& __stream)
        -> decltype(auto)
        {
            auto __cursor = __stream.begin();

            return matches(__parser, __cursor, __stream.end());
        }

        
        template<
            typename ... params_t, 
            typename stream_t>
        inline auto
        matches(
            matcher::matcher<params_t...> const& __matcher,
            stream_t const& __stream)
        -> decltype(auto)
        {
            auto __cursor = __stream.begin();

            return matches(__matcher, __cursor, __stream.end());
        }
      

         template<
            typename ... params_t, 
            typename iterator_t>
        inline auto
        parse(
            parser::parser<params_t...> const& __parser,
            iterator_t& __cursor,
            iterator_t const& __end, 
            __target<parser::parser<params_t...>>& __tgt)
        {
            auto __save = __cursor; 

            if(__parser(__cursor, __end))
                return __parser(__save, __cursor, __tgt);
            else 
                return false;
        }

        
        template<
            typename ... params_t, 
            typename iterator_t>
        inline auto
        parse(
            caster::caster<params_t...> const& __caster,
            iterator_t& __cursor,
            iterator_t const& __end, 
            __target<caster::caster<params_t...>>& __tgt)
        -> decltype(auto)
        {
            return __caster(__cursor, __end, __tgt);
        }

         template<
            typename ... params_t, 
            typename stream_t>
        inline auto
        parse(
            parser::parser<params_t...> const& __parser,
            stream_t const& __stream, 
            __target<parser::parser<params_t...>>& __tgt)
        -> decltype(auto)
        {
            auto __cursor = __stream.begin();

            return parse(__parser, __cursor, __stream.end(), __tgt);
        }

        
        template<
            typename ... params_t, 
            typename stream_t>
        inline auto
        parse(
            caster::caster<params_t...> const& __caster,
            stream_t const& __stream, 
            __target<caster::caster<params_t...>>& __tgt)
        -> decltype(auto)
        {
            auto __cursor = __stream.begin();

            return parse(__caster, __cursor, __stream.end(), __tgt);
        }

        namespace matcher
        {
            extern constexpr auto 
            range =
                [](auto __min, auto __max)
                {
                    return 
                    make_matcher(
                    [__min, __max](auto& __cursor, auto const& __end)
                    {
                        return 
                            __min <= *__cursor && *__cursor <= __max ?
                            (++__cursor, true) : 
                            false;
                    });
                };

            extern constexpr auto digit = range('0', '9');

            extern constexpr auto 
            sym = 
                [] (auto __symbol)
                {
                    return 
                    make_matcher(
                    [__symbol](auto& __cursor, auto const& __end)
                    {
                        return 
                            *__cursor == __symbol ? 
                            (++__cursor, true) : 
                            false;
                    });
                };
        }

        namespace caster
        {
            extern constexpr auto 
            sym = 
                [](auto __symbol) 
                {
                    using char_t = meta::decay<decltype(__symbol)>;
                    
                    return 
                    make_caster<char_t>(
                    [__symbol](auto& __cursor, auto const& __end, auto& __tgt)
                    {
                        if(matcher::sym(__symbol)(__cursor, __end))   
                        {   
                            --__cursor; 
                            __tgt = static_cast<char_t>(*__cursor); 
                            ++__cursor; 
                            return true;
                        }
                        else 
                            return false;
                    });
                };

            extern constexpr auto 
            range = 
                [](auto __min, auto __max) 
                {
                    using char_t = meta::decay<decltype(__min)>;
                    
                    return 
                    make_caster<char_t>(
                    [__min, __max](auto& __cursor, auto const& __end, auto& __tgt)
                    {
                        if(matcher::range(__min, __max)(__cursor, __end))   
                        {   
                            --__cursor; 
                            __tgt = static_cast<char_t>(*__cursor); 
                            ++__cursor; 
                            return true;
                        }
                        else 
                            return false;
                    });
                };

            template<
                typename int_t>
            extern constexpr 
            auto digit = 
                    make_caster<meta::decay<int_t>>(
                        tern(bind(matcher::digit, $0, $1))
                        [--$0, $2 = compose(static_cast_<meta::decay<int_t>>, (*$0) - val('0')), ++$0, val(true)]
                        [val(false)]);

          
        }

        namespace parser
        {
            template<
                typename char_t>
            constexpr auto 
            sym(
                char_t symbol_c)
            {
                return matcher::sym(symbol_c) 
                    && caster::sym(symbol_c);
            }

            template<
                typename char_t>
            constexpr auto 
            range(
                char_t min_c, 
                char_t max_c)
            {
                return matcher::range(min_c, max_c)
                    && caster::range(min_c, max_c);
            }
        }
    }
}

#endif // !__THODD_LANG2_HPP__