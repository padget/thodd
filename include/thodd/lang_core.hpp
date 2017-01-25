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
                thodd::detail::range<iterator_t> range;
                
                operator bool () const 
                {
                    return range.begin() != range.end();
                }

                
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