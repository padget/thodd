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
            struct token
            {
                using range_t = thodd::detail::range<iterator_t>;

                range_t<iterator_t> range;
                list<range_t<iterator_t>> subranges;
                
                operator bool () const 
                {
                    return range.begin() != range.end();
                }

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
            auto const& __begin, 
            auto const&__end)
        {
            return 
            detail::token<meta::decay<decltype(__begin)>>
            {thodd::range(__begin, __end)};
        }
    }
}

#endif