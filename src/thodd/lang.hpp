#ifndef __ATOM_LANG2_HPP__
#  define __ATOM_LANG2_HPP__

#  include <limits>

#  include <thodd/tuple.hpp> 
#  include <thodd/law.hpp>
#  include <thodd/meta.hpp>
#  include <thodd/functional.hpp>
#  include <thodd/variant.hpp>

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
                typename algorithm_t>
            struct matcher
            {
                algorithm_t algo;

                template<
                    typename iterator_t>
                inline auto
                operator() (
                    iterator_t& __cursor, 
                    iterator_t const& __end) const
                {
                    auto&& __res = algo(__cursor, __end);
                    //react(__cursor, __end, __res);

                    return __res;
                }

                // template<
                //     typename oreactor_t>
                // constexpr auto 
                // operator[](
                //     oreactor_t const& __react) const
                // {
                //     return matcher<algorithm_t, meta::decay<oreactor_t>>{algo, __react};
                // }
            };

        
            struct matcher_tag{};
            extern constexpr matcher_tag match{};


            template<
                typename algorithm_t>
            constexpr auto
            operator << (
                matcher_tag const&, 
                algorithm_t&& __algo)
            -> matcher<meta::decay<algorithm_t>>
            {
                return {perfect<algorithm_t>(__algo)};
            }
        
        
            template<
                typename ... algorithms_t>
            struct alternative
            {
                tuple<algorithms_t...> algos;

                template<
                    typename iterator_t, 
                    size_t ... indexes_c>
                inline auto
                operator()(
                    iterator_t& __cursor, 
                    iterator_t const& __end,
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
                typename l_algorithm_t, 
                typename r_algorithm_t>
            constexpr auto
            operator | (
                matcher<l_algorithm_t> const& __left, 
                matcher<r_algorithm_t> const& __right)
            -> decltype(auto)
            {
                using left_or_right_t = alternative<meta::decay<l_algorithm_t>, meta::decay<r_algorithm_t>>;

                return match << left_or_right_t{make_tuple(__left.algo, __right.algo)};
            }

            
            template<
                typename ... l_algorithms_t, 
                typename r_algorithm_t>
            constexpr auto
            operator | (
                matcher<alternative<l_algorithms_t...>> const& __left, 
                matcher<r_algorithm_t> const& __right)
            -> decltype(auto)
            {
                using lefts_or_right_t = alternative<meta::decay<l_algorithms_t>..., meta::decay<r_algorithm_t>>;

                return match << lefts_or_right_t{__left.algo.algos + __right.algo};
            }


            template<
                typename l_algorithm_t, 
                typename ... r_algorithms_t>
            constexpr auto
            operator | (
                matcher<l_algorithm_t> const& __left, 
                matcher<alternative<r_algorithms_t...>> const& __right)
            -> decltype(auto)
            {
                using left_or_rights_t = alternative<meta::decay<l_algorithm_t>, meta::decay<r_algorithms_t>...>;

                return match << left_or_rights_t{__left.algo + __right.algo.algos};
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

                return match << lefts_or_rights_t{__left.algo.algos + __right.algo.algos};
            }




            template<
                typename algorithm_t>
            struct some
            {
                algorithm_t algo;

                size_t min_c{0};
                size_t max_c{1};

                constexpr auto 
                operator() (
                    size_t __min, 
                    size_t __max) const
                {
                    return match << some<algorithm_t> {algo, __min, __max};
                }


                constexpr auto 
                operator() (
                    size_t __strict) const
                {
                    return match << some<algorithm_t> {algo, __strict, __strict};
                }


                template<
                    typename iterator_t>
                inline auto 
                operator() (
                    iterator_t& __cursor, 
                    iterator_t const& __end) const
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
                typename r_algorithm_t>
            constexpr auto 
            operator ~ (
                matcher<r_algorithm_t> const& __right)
            -> decltype(auto)
            {
                using some_t = some<meta::decay<r_algorithm_t>>;

                return some_t{__right.algo};
            }

            template<
                typename r_algorithm_t>
            constexpr auto
            operator * (
                matcher<r_algorithm_t> const& __right)
            -> decltype(auto)
            {
                return (~__right)(0, infinity);
            }


            template<
                typename r_algorithm_t>
            constexpr auto
            operator + (
                matcher<r_algorithm_t> const& __right)
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
                typename l_algorithm_t, 
                typename r_algorithm_t>
            constexpr auto
            operator >> (
                matcher<l_algorithm_t> const& __left,
                matcher<r_algorithm_t> const& __right)
            {
                using follow_t = follow<meta::decay<l_algorithm_t>, meta::decay<r_algorithm_t>>;

                return match << follow_t{make_tuple(__left.algo, __right.algo)};
            }



            template<
                typename ... l_algorithms_t, 
                typename r_algorithm_t>
            constexpr auto
            operator >> (
                matcher<follow<l_algorithms_t...>> const& __left,
                matcher<r_algorithm_t> const& __right)
            {
                using follow_t = follow<meta::decay<l_algorithms_t>..., meta::decay<r_algorithm_t>>;

                return match << follow_t{__left.algo.algos + __right.algo};
            }

            
            template<
                typename l_algorithm_t, 
                typename ... r_algorithms_t>
            constexpr auto
            operator >> (
                matcher<l_algorithm_t> const& __left,
                matcher<follow<r_algorithms_t...>> const& __right)
            {
                using follow_t = follow<meta::decay<l_algorithm_t>, meta::decay<r_algorithms_t>...>;

                return match << follow_t{__left.algo + __right.algo.algos};
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

                return match << follow_t{__left.algo.algos + __right.algo.algos};
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
            /// # typename algorithm_t  algorithme encaspulé
            /// # typename target_t     type cible de l'algorithme
            template<
                typename algorithm_t, 
                typename target_t, 
                typename reactor_t = detail::nothing>
            struct caster
            {
                using target = target_t;

                algorithm_t algo;
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
                    react(__cursor, __end, __res, __tgt);
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
                    return caster<algorithm_t, 
                                  target_t, 
                                  meta::decay<oreactor_t>>{algo, __react};
                }
            };

        
            template<
                typename target_t>
            struct caster_tag{};

            template<
                typename target_t>
            extern constexpr caster_tag<target_t> cast{};


            template<
                typename target_t,
                typename algorithm_t>
            constexpr auto
            operator << (
                caster_tag<target_t> const&, 
                algorithm_t&& __algo)
            -> caster<meta::decay<algorithm_t>, target_t>
            {
                return {perfect<algorithm_t>(__algo)};
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
                
                return cast<targets_t> << left_or_right_t{make_tuple(__left, __right)};
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

                return cast<target_t> << lefts_or_right_t{__left.algo.casters + __right};
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

                return cast<target_t> << left_or_rights_t{__left + __right.algo.algos};
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

                return cast<target_t> << lefts_or_rights_t{__left.algo.casters + __right.algo.casters};
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
                    return cast<target> << some<caster_t>{caster, __min, __max};
                }

                
                constexpr auto 
                operator() (
                    size_t __strict) const
                {
                    return cast<target> << some<caster_t>{caster, __strict, __strict};
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

                return cast<target_t> << follow_t{make_tuple(__left, __right)};
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

                return cast<target_t> << follow_t{__left.algo.casters + __right};
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

                return cast<target_t> << follow_t{__right + __left.algo.casters};
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

                return cast<target_t> << follow_t{__left.algo.casters + __right.algo.casters};
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
                return (~__right)(1, infinity);
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
            template<
                typename char_t>
            constexpr auto
            range( 
                char_t min_c, 
                char_t max_c)
            {
                return match << 
                         if_(val(min_c) <= *$0 && *$0 <= val(max_c)) 
                            ((++$0, val(true)))
                        .else_
                            (val(false));   
            }


            extern constexpr auto digit = range('0', '9');


            template<
                typename char_t>
            constexpr auto 
            sym(
                char_t symbol_c)
            {
                return match << 
                        if_(val(symbol_c) == *$0) 
                            ((++$0, val(true)))
                       .else_
                            (val(false));
            }


            template<
                typename char_t>
            constexpr auto
            word(
                char_t const& __char)
            {
                return sym(__char);
            }

            template<
                typename char_t,
                typename char2_t,
                typename ... chars_t>
            constexpr auto
            word(
                char_t const& __char,
                char2_t const& __char2,
                chars_t const&... __chars)
            {
                return sym(__char) >> word(__char2, __chars...) ;
            }
        }

        namespace caster
        {

            template<
                typename char_t>
            constexpr auto
            sym(
                char_t symbol_c)
            {
                return cast<meta::decay<char_t>> 
                    << if_(bind(matcher::sym(symbol_c), $0, $1))
                           ((--$0, $2 = compose(static_cast_(type_<meta::decay<char_t>>{}), *$0), ++$0, val(true)))
                       .else_
                            (val(false));
            }

            template<
                typename char_t> 
            constexpr auto
            range(
                char_t min_c, 
                char_t max_c)
            {
                return cast<meta::decay<char_t>> << 
                        if_(bind(matcher::range(min_c, max_c), $0, $1))
                           ((--$0, $2 = compose(static_cast_(type_<meta::decay<char_t>>{}), *$0), ++$0, val(true)))
                       .else_
                           (val(false));
            }

            template<
                typename int_t>
            extern constexpr 
            auto digit = cast<meta::decay<int_t>> <<
                            if_(bind(matcher::digit, $0, $1))
                                ((--$0, $2 = compose(static_cast_(type_<meta::decay<int_t>>{}), (*$0) - val('0')), ++$0, val(true)))
                            .else_
                                (val(false));

           
            
            template<
                typename char_t>
            constexpr auto
            word(
                char_t const& __char)
            {
                return sym(__char);
            }

            template<
                typename char_t,
                typename char2_t,
                typename ... chars_t>
            constexpr auto
            word(
                char_t const& __char,
                char2_t const& __char2,
                chars_t const&... __chars)
            {
                return sym(__char) >> word(__char2, __chars...) ;
            }
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

#endif // !__ATOM_LANG2_HPP__



/*
 auto __integer = +caster::short_;
    auto __integer_result = __integer.attr();

    string __str_integer{"123"};
    auto __begin = __str_integer.begin(),
         __end = __str_integer.end(); 

    logger<root>::info(std::boolalpha, __integer(__begin, __end, __integer_result));

    auto __integer_to_int = 
        [](auto const& __attr)
        {
            auto __res = 0;
            auto __unit = 1u;
            
            auto __begin = __attr.begin();
            auto __end   = --__attr.end();

            while(__end != __begin)
            {
                __res += (*__end) * __unit;
                __unit *= 10;
                --__end;
            }

            __res += (*__end) * __unit;
            __unit *= 10;

            return __res;
        };

    logger<root>::info(" resultat : ", __integer_to_int(__integer_result));
*/