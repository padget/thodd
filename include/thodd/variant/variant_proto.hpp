#ifndef __THODD_VARIANT_VARIANT_PROTO_HPP__
#  define __THODD_VARIANT_VARIANT_PROTO_HPP__

#  include <thodd/meta/pack/transfer.hpp>
#  include <thodd/meta/pack/unique.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/meta/traits/decay.hpp>

namespace 
thodd::proto
{
    template<
        typename ...>
    struct pack {};

    template<
        typename type_t, 
        typename ... types_t>
    struct variant;

    template<
        typename type_t, 
        typename ... types_t>
    using variant_unique = 
        meta::transfer_t<
            variant,
            meta::unique_t<
                pack<type_t, types_t...>>>;

    template<
        typename type_t, 
        typename derived_t>
    struct variant_caster
    {
        virtual ~variant_caster() = default;

        operator type_t&()
        {
            return 
            dynamic_cast<
                derived_t*>
            (this)->template 
            get<type_t>();
        }

        operator type_t const&() const
        {
            return 
            dynamic_cast<
                derived_t const*>
            (this)->template 
            get<type_t const>();
        }
    };

    struct variant_item_base
    {
        virtual ~variant_item_base() = default;
    };

    template<
        typename type_t>
    struct variant_item:
        variant_item_base
    {
        type_t item;

    public:
        variant_item(
            type_t&& __item) :
            item{thodd::rvalue(__item)} {}
        
        
        variant_item(
            type_t& __item) :
            item{__item} {}

        
        variant_item(
            type_t const& __item) :
            item{__item} {}


        virtual ~variant_item() = default;

    public:
        variant_item& 
        operator = (
            type_t const& __item)
        {
            item = __item;
            return *this;
        }


        variant_item& 
        operator = (
            type_t&& __item)
        {
            item = thodd::rvalue(__item);
            return *this;
        }
    };
    

    template<
        typename type_t,
        typename ... types_t>
    class variant:
        variant_caster<type_t, variant<type_t, types_t...>>, 
        variant_caster<types_t, variant<type_t, types_t...>>...
    {
    private:
        size_t m_index = -1;
        variant_item_base* m_data{nullptr};

    public:    
        virtual ~variant() = default;

    public:
        template<
            typename otype_t>
        variant(otype_t&& __data) : 
           m_data(new variant_item<meta::decay_t<otype_t>>{static_cast<otype_t&&>(__data)}) {}

    public:
        inline auto const 
        index() const 
        {
            return m_index;
        }

    public:
        template<
            typename otype_t>
        inline auto 
        get() &
        -> decltype(auto)
        {
            return 
            static_cast<otype_t&>(*m_data);
        }


        template<
            typename otype_t>
        inline auto 
        get() const &
        -> decltype(auto)
        {
            return 
            static_cast<otype_t const&>(*m_data);
        }


        
        template<
            typename otype_t>
        inline auto 
        get() &&
        -> decltype(auto)
        {
            return 
            static_cast<otype_t&&>(*m_data);
        }
    };
}

#endif