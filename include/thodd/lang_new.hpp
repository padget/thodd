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
            typename matcher_t, 
            typename caster_t,
            typename reactor_t = meta::decay<decltype(nothing)>>
        struct parser
        {
            matcher_t match;
            caster_t cast;
            reactor_t react;

            inline auto 
            operator()(
                auto& __cursor, 
                auto const& __end) const
            {
                return match(__cursor, __end);
            }

            
            inline auto
            operator()(
                auto& __cursor, 
                auto& __end, 
                auto& __tgt) const
            {
                auto __save = __cursor;
                
                if(match(__cursor, __end))
                {   
                    cast(__save, __cursor, __tgt);
                    react(__tgt);
                    return true;
                }
                else 
                {
                    __cursor = __save 
                    return false;
                }
            }
        };

        
    }
}

#endif // !__THODD_LANG2_HPP__