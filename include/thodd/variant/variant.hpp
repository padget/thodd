#ifndef __THODD_VARIANT_HPP__
#  define __THODD_VARIANT_HPP__

#  include <thodd/core/expand.hpp>
#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/perfect.hpp>

#  include <thodd/meta/pack/transfer.hpp>

#  include <thodd/pointer/shared.hpp>

#  include <thodd/variant/variant_caster.hpp>

namespace thodd
{
    /// #return the size of the 
    ///         type with the 
    ///         largest memory footprint 
    template<   
        template<
            typename...> 
        typename pack_t,
        typename type_t, 
        typename ... types_t>
    constexpr size_t
    biggest_sizeof(
        pack_t<type_t, types_t...> const&)
    {
        size_t __biggest{sizeof(type_t)};
        expand{ ((__biggest = (sizeof(types_t) > __biggest ? sizeof(types_t) : __biggest)), 0)... };

        return __biggest;
    }


    /// #struct variant
    template<
        typename type_t,   
        typename ... types_t>
    class variant:
        public variant_caster<
                    variant<type_t, types_t...>,
                    meta::transfer<meta::unique<meta::pack<type_t, types_t...>>, variant>>
    {
    private:
        /// holder base class
        /// that enables placeholding
        /// for variant class
        struct holder_base 
        {
            virtual ~holder_base() = default;
        };

        template< 
            typename wtype_t>
        struct holder : 
                holder_base
        {
            wtype_t data;

            holder(
                wtype_t const& __data):
                data(__data) {}
        };

        shared<holder_base> holded;

    public:
        variant() = default;

        template<
            typename wtype_t>
        variant(
            wtype_t&& __wt) :
            holded(new holder<wtype_t>(perfect<wtype_t>(__wt)))
        {
           /* static_assert(meta::contains_f(
                            type_<wtype_t>{}, 
                            meta::pack<type_t, types_t...>{}), 
                          "the type must be contained "
                          "in variant possible types");*/
        }

        variant(
            variant const& __other):
            holded(__other.holded) {}

        variant(
            variant&& __other):
            holded(rvalue(__other.holded)) {}

        virtual ~variant() = default;

        template<
            typename wtype_t>
        variant& 
        operator=(
            wtype_t&& __wt)
        {
            /*static_assert(meta::contains_f(
                            type_<wtype_t>{}, 
                            meta::pack<type_t, types_t...>{}), 
                          "the type must be contained "
                          "in variant possible type !!");
                          */
            holded.reset(new holder<wtype_t>(perfect<wtype_t>(__wt)));
            
            return *this;
        }


        variant& 
        operator=(
            variant const& __other)
        {
            if(this != &__other)
                holded = __other.holded;

            return *this;
        }
        

        variant& 
        operator=(
            variant&& __other)
        {
            if(this != &__other)
                holded = rvalue(__other.holded);

            return *this;
        }


        template<
            typename wtype_t>
        wtype_t const&
        get() const
        {
            return 
            dynamic_cast<
                holder<wtype_t> const*>
            (holded.get())->data;
        }


        template<
            typename wtype_t>
        wtype_t&
        get()
        {
            if(!holded)
                holded.reset(new holder<wtype_t>(wtype_t()));

            return 
            dynamic_cast<
                holder<wtype_t>*>
            (holded.get())->data;
        }
    };
}

#endif
