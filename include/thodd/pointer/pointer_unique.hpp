#ifndef __THODD_POINTER_UNIQUE_HPP__
#  define __THODD_POINTER_UNIQUE_HPP__

#  include <thodd/pointer_handler.hpp>

namespace thodd
{ 
    template<
        typename type_t>
    class unique:
        public handler<type_t>
    {
        template<
            typename otype_t>
        friend class unique;

    public:
        virtual
        ~unique()
        {
            this->destroy();
        }

        unique(unique const&) = delete;
        unique& operator=(unique const&) = delete;

        template<
            typename otype_t>
        unique(unique<otype_t> const&) = delete;


        unique() = default;
        unique(unique&&) = default;
        unique& operator=(unique&&) = default;

        explicit
        unique(
            type_t* _pointer):
            handler<type_t>{_pointer} {}

        unique(std::nullptr_t) {}

        template<
            typename otype_t>
        unique(
            unique<otype_t>&& _other):
            handler<type_t>{_other} {};

        template<
            typename otype_t>
        unique& operator=(
            unique<otype_t>&& _other)
        {
            this->handler<type_t>::operator=(_other);
            return *this;
        }

        unique&
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
            unique const& _other)
        {
            return this->operator ==(_other.get());
        }

    };

    template<
        typename type_t,
        typename ... args_t>
    unique<type_t>
    make_unique(
        args_t&&..._args)
    {
        return {new type_t{perfect<args_t>(_args)...}};
    }
}

#endif