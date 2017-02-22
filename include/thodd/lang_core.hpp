#ifndef __THODD_LANG_CORE_HPP__
#  define __THODD_LANG_CORE_HPP__

#  include <thodd/meta.hpp>
#  include <thodd/containers.hpp>

namespace thodd
{
    namespace lang
    {
        namespace detail
        {
            template<
                typename iterator_t>
            class token final 
            {
            public:
                using range_t = thodd::detail::range<iterator_t>;

                size_t index{0u};
                bool valid{false};
                range_t range;
                thodd::list<token> subranges;
                
                operator bool () const 
                {
                    return valid;
                }
            
                token() = default;
                token(token const&) = default;
                token(token&&) = default; 
                ~token() = default;
                token& operator=(token const&) = default;
                token& operator=(token&&) = default;

            public:
                token(
                    bool __valid, 
                    size_t __index,
                    iterator_t const& __begin, 
                    iterator_t const& __end) :
                    index(__index),
                    valid(__valid),
                    range{thodd::range(__begin, __end)} {}
            
            
                token(
                    bool __valid, 
                    size_t __index,
                    iterator_t const& __begin, 
                    iterator_t const& __end, 
                    list<token> const& __subranges) :
                    index(__index), 
                    valid(__valid),
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
            auto const& __valid,
            auto const& __index,
            auto const& __begin, 
            auto const& __end)
        {
            return 
            detail::token<meta::decay<decltype(__begin)>>
            (__valid, __index, __begin, __end);
        }

        inline auto 
        token(
            auto const& __valid,
            auto const& __index,
            auto const& __begin, 
            auto const& __end, 
            auto&& __subranges)
        {
            return 
            detail::token<meta::decay<decltype(__begin)>>
            (__valid, __index, __begin, __end, perfect<decltype(__subranges)>(__subranges));
        }
    }
}

#endif