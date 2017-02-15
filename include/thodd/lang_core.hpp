#ifndef __THODD_LANG_CORE_HPP__
#  define __THODD_LANG_CORE_HPP__

#  include <thodd/meta.hpp>
#  include <thodd/containers.hpp>

namespace thodd
{
    namespace lang
    {
        template<
            typename type_t>
        using __target = typename type_t::target;
        

        namespace detail
        {
            template<
                typename iterator_t>
            class token final 
            {
            public:
                using range_t = thodd::detail::range<iterator_t>;

                size_t index{0u};
                range_t range;
                thodd::list<token> subranges;
                
                operator bool () const 
                {
                    return range.begin() != range.end();
                }
            
                token() = default;
                token(token const&) = default;
                token(token&&) = default; 
                ~token() = default;
                token& operator=(token const&) = default;
                token& operator=(token&&) = default;

            public:
                token(
                    size_t __index,
                    iterator_t const& __begin, 
                    iterator_t const& __end) :
                    index(__index),
                    range{thodd::range(__begin, __end)} {}
            
            
                token(
                    size_t __index,
                    iterator_t const& __begin, 
                    iterator_t const& __end, 
                    list<token> const& __subranges) :
                    index(__index),
                    range{thodd::range(__begin, __end)}, 
                    subranges{__subranges} {}

            public:    
                inline auto const
                size()
                {
                    return range.size();
                }

                inline auto 
                begin() 
                {
                    return range.begin();
                }

                inline auto const
                begin() const
                {
                    return range.begin();
                }

                inline auto 
                end() 
                {
                    return range.end();
                }

                inline auto const
                end() const
                {
                    return range.end();
                }    

            public:
                inline auto const
                sub_size()
                {
                    return subranges.size();
                }
            
                inline auto 
                sub_begin() 
                {
                    return subranges.begin();
                }

                inline auto const
                sub_begin() const
                {
                    return subranges.begin();
                }

                inline auto 
                sub_end() 
                {
                    return subranges.end();
                }

                inline auto const
                sub_end() const
                {
                    return subranges.end();
                }
            };
        }

        inline auto 
        token(
            auto const& __index,
            auto const& __begin, 
            auto const& __end)
        {
            return 
            detail::token<meta::decay<decltype(__begin)>>
            (__index, __begin, __end);
        }

        inline auto 
        token(
            auto const& __index,
            auto const& __begin, 
            auto const& __end, 
            auto&& __subranges)
        {
            return 
            detail::token<meta::decay<decltype(__begin)>>
            (__index, __begin, __end, perfect<decltype(__subranges)>(__subranges));
        }
    }
}

#endif