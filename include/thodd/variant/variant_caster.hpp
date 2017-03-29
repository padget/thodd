#ifndef __THODD_VARIANT_VARIANT_CASTER_HPP__
#  define __THODD_VARIANT_VARIANT_CASTER_HPP__

#  include <thodd/variant/variant_caster_item.hpp>

namespace
thodd
{
    template<
        typename variant_t, 
        typename items_t>
    struct variant_caster;


    template<
        typename variant_t, 
        template<typename ...> typename pack_t,
        typename ... items_t>
    struct variant_caster<variant_t, pack_t<items_t...>>:
        public variant_caster_item<items_t, variant_t>...
    {
        virtual ~variant_caster() = default;
    };
}

#endif