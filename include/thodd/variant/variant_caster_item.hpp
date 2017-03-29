#ifndef __THODD_VARIANT_VARIANT_CASTER_ITEM_HPP__
#  define __THODD_VARIANT_VARIANT_CASTER_ITEM_HPP__

namespace 
thodd
{
    template<
        typename type_t, 
        typename variant_t>
    struct variant_caster_item
    {
        virtual ~variant_caster_item() = default;

        operator type_t&()
        {
            return 
            dynamic_cast<
                variant_t*>
            (this)->template 
            get<type_t>();
        }

        operator type_t const&() const
        {
            return 
            dynamic_cast<
                variant_t const*>
            (this)->template 
            get<type_t const>();
        }
    };
}

#endif