#ifndef __THODD_VARIANT_VARIANT_PROTO_HPP__
#  define __THODD_VARIANT_VARIANT_PROTO_HPP__

#  include <thodd/meta/pack/transfer.hpp>
#  include <thodd/meta/pack/unique.hpp>
#  include <thodd/meta/traits/decay.hpp>
#  include <thodd/meta/pack/indexof.hpp>
#  include <thodd/meta/pack/at.hpp>

#  include <thodd/core/sequence.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/expand.hpp>

#  include <thodd/pointer/shared.hpp>


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
        public variant_caster<type_t, variant<type_t, types_t...>>, 
        public variant_caster<types_t, variant<type_t, types_t...>>...
    {
    private:
        long long int m_index = -1;
        shared<variant_item_base> m_data{nullptr};


    public:    
        virtual ~variant() = default;

    public:
        template<
            typename otype_t>
        variant(otype_t&& __data) : 
            m_index{
                meta::indexof(
                    pack<type_t, types_t...>{}, 
                    meta::decay(
                        meta::type_<otype_t>{}))},
            m_data{
               new variant_item<meta::decay_t<otype_t>>
               {static_cast<otype_t&&>(__data)}} {}

    public:
        variant(variant const&) = default;
        variant(variant&&) = default;


    public:
        template<
            typename otype_t>
        inline variant&
        operator = (   
            otype_t&& __data) 
        {
            m_index = 
                 meta::indexof(
                    pack<type_t, types_t...>{}, 
                    meta::decay(
                        meta::type_<otype_t>{}));
            m_data = 
                new variant_item<meta::decay_t<otype_t>>
                {static_cast<otype_t&&>(__data)};

            return *this;
        } 

    public:
        variant& operator = (variant const&) = default;
        variant& operator = (variant&&) = default;


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
            using derived_t = variant_item<otype_t>;
            
            return 
            static_cast<otype_t&>(
                dynamic_cast<derived_t&>(*m_data).item);
        }


        template<
            typename otype_t>
        inline auto 
        get() const &
        -> decltype(auto)
        {
            using derived_t = variant_item<otype_t>;
            
            return 
            static_cast<otype_t const&>(
                dynamic_cast<derived_t const&>(*m_data).item);
        }

        
        template<
            typename otype_t>
        inline auto 
        get() &&
        -> decltype(auto)
        {
            using derived_t = variant_item<otype_t>;
            
            return 
            static_cast<otype_t&&>(
                dynamic_cast<derived_t&&>(*m_data).item);
        }

    
    private:
        template<
            size_t ... indexes_c>
        inline auto
        visit(
            auto&& __func, 
            sequence<size_t, indexes_c...> const&)
        {
            expand{ (m_index == indexes_c ? __func, 0)...};
        }


    public:
        inline auto
        visit(
            auto&& __func)
        -> decltype(auto)
        {
            return 
            visit(
                perfect<decltype(__func)>(__func), 
                make_sequence(
                    igral<sizeof...(types_t) + 1>{});
            )
        }
    };
}

#endif