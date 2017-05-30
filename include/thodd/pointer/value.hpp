#ifndef __THODD_POINTER_VALUE_HPP__
#  define __THODD_POINTER_VALUE_HPP__

#  include <thodd/pointer/handler.hpp>

namespace thodd
{ 
    template<
        typename type_t>
    class value:
        public handler<type_t>
    {
        template<
            typename otype_t>
        friend class value;

    public:
        virtual
        ~value()
        {
            this->destroy();
        }

        value(
            value const& __other) :
            handler<type_t>(__other ? new type_t(*__other) : nullptr) {}

        value& 
        operator=(
            value const& __other) 
        {
            if(this != &__other)
                this->handler<type_t>::operator = (__other ? new type_t(*__other) : nullptr);
        
            return *this;
        }

        template<
            typename otype_t>
        value(
            value<otype_t> const& __other) :
            handler<type_t>(__other ? new type_t(*__other) : nullptr) {}


        value() = default;
        value(value&&) = default;
        value& operator=(value&&) = default;

        explicit
        value(
            type_t* _pointer):
            handler<type_t>{_pointer} {}

        value(std::nullptr_t) {}

        template<
            typename otype_t>
        value(
            value<otype_t>&& _other):
            handler<type_t>{_other} {};

        template<
            typename otype_t>
        value& operator=(
            value<otype_t>&& _other)
        {
            this->handler<type_t>::operator=(_other);
            return *this;
        }

        value&
        operator=(
            type_t* _other)
        {
            if(_other != this->get())
            {
                this->destroy();
                this->handler<type_t>::operator =(_other);
            }

            return *this;
        }


        inline bool const
        operator==(
            value const& _other)
        {
            return this->operator ==(_other.get());
        }

    };

    template<
        typename type_t,
        typename ... args_t>
    value<type_t>
    make_value(
        args_t&&..._args)
    {
        return {new type_t{perfect<args_t>(_args)...}};
    }
}

#endif