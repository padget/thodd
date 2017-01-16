/*
 * pointers.hpp
 *
 *  Created on: 5 août 2016
 *      Author: padget
 */

#ifndef ATOM_POINTERS_HPP_
#  define ATOM_POINTERS_HPP_

#  include <thodd/law.hpp>
#  include <thodd/require.hpp>

namespace thodd
{
    ATOM_EXCEPTION(
        null_pointer_exception, 
        "the pointer is null")

    template<
        typename type_t>
    class handler
    {
        type_t* m_handled{nullptr};

    public:
        handler() = default;
        handler(handler const&) = default;
        handler(handler&&) = default;
        virtual ~handler() = default;
        handler& operator=(handler const&) = default;
        handler& operator=(handler&&) = default;


    public:
        explicit
        handler(
            type_t* _handled):
            m_handled{_handled} {}

        handler(std::nullptr_t) {}


        template<
            typename otype_t>
        handler(
            handler<otype_t> const& _other):
            m_handled{_other.m_handled} {}


        template<
            typename otype_t>
        handler(
            handler<otype_t>&& _other):
            m_handled{move(_other.m_handled)} {}


        handler&
        operator=(
            type_t* _other)
        {
            reset(_other);
            return *this;
        }

        template<
            typename otype_t>
        handler&
        operator=(
            handler<otype_t> const& _other)
        {
            reset(_other.m_handled);
            return *this;
        }


        template<
            typename otype_t>
        handler&
        operator=(
            handler<otype_t>&& _other)
        {
            reset(move(_other.m_handled));
            return *this;
        }


    public:
        type_t*
        get() const
        {
            return m_handled;
        }

        type_t*
        operator->() const
        {
            return m_handled;
        }


        type_t const&
        operator*() const
        {
            go<contract>(
                require(ref(m_handled) != val(nullptr))
                > throw_<null_pointer_exception>());

            return *m_handled;
        }

        type_t&
        operator*()
        {
            go<contract>(
                require(ref(m_handled) != val(nullptr))
                > throw_<null_pointer_exception>());

            return *m_handled;
        }

        inline type_t&
        operator[](
            size_t const& _index)
        {
            go<contract>(
                require(!*ref(this)) 
                > throw_<null_pointer_exception>());

            return *(m_handled + _index);
        }

        inline type_t const&
        operator[](
            size_t const& _index) const
        {
            go<contract>(
                require(!*ref(this)) 
                > throw_<null_pointer_exception>());
           
            return *(m_handled + _index);
        }

        inline bool const
        operator==(
            type_t* _other) const
        {
            return m_handled == _other;
        }

        inline bool const
        operator==(
            handler const& _other) const
        {
            return this->operator ==(_other.m_handled);
        }


    public:
        inline void
        destroy() const
        {
            thodd::destroy(m_handled);
        }


        inline void
        reset(
            type_t* _handled)
        {
            m_handled = _handled;
        }


        inline bool const
        is_null() const
        {
            return m_handled == nullptr;
        }

        inline
        operator bool() const
        {
            return !is_null();
        }
    };


    template<
            typename type_t,
            typename ... args_t>
    handler<type_t>
    make_handler(
        args_t&&... _args)
    {
        return {new type_t{perfect<args_t>(_args)...}};
    }


    template<
        typename type_t>
    class shared final:
        public handler<type_t>
    {

        template<typename otype_t>
        friend class shared;

        class shared_counter
        {
            size_t m_count{1};

        public:
            inline void
            increase()
            {
                ++m_count;
            }

            inline void
            decrease()
            {
                if(!alone())
                    --m_count;
            }

            inline bool const
            alone() const
            {
                return m_count == 1;
            }
        };

    private:
        handler<shared_counter> m_counter{new shared_counter{}};

    public:
        virtual ~shared()
        {
             this->release();
        }

        shared() = default;


        explicit
        shared(
            type_t* _pointer) :
            handler<type_t>{_pointer} {}

        shared(std::nullptr_t) {}


        template<
            typename otype_t>
        shared(
            shared<otype_t> const& _other):
            handler<type_t>{_other},
            m_counter{_other.m_counter}
        {
            m_counter->increase();
        }

        shared(
            shared const& _other):
            handler<type_t>{_other},
            m_counter{_other.m_counter}
        {
            m_counter->increase();
        }


        template<
            typename otype_t>
        shared(
            shared<otype_t>&& _other):
            handler<type_t>{_other},
            m_counter{move(_other.m_counter)} {}


        shared(
            shared&& _other):
            handler<type_t>{_other},
            m_counter{move(_other.m_counter)} {}


        template<
            typename otype_t>
        shared&
        operator=(
            shared<otype_t> const& _other)
        {
            release();
            this->handler<type_t>::operator =(_other);
            this->m_counter = _other.m_counter;
            return *this;
        }


        shared&
        operator=(
            shared const& _other)
        {
            if(this != &_other)
            {
                release();
                this->handler<type_t>::operator =(_other);
                this->m_counter = _other.m_counter;
            }

            return *this;
        }


        template<
            typename otype_t>
        shared&
        operator=(
            shared<otype_t>&& _other)
        {
            release();
            this->handler<type_t>::operator =(_other);
            this->m_counter = move(_other.m_counter);
            return *this;
        }


        shared&
        operator=(
            shared&& _other)
        {
            if(this != &_other)
            {
                release();
                this->handler<type_t>::operator =(_other);
                this->m_counter = move(_other.m_counter);
            }

            return *this;
        }


        shared&
        operator=(
            type_t* _other)
        {
            if(_other != this->get())
            {
                release();
                this->reset(_other);
                this->m_counter.reset(new shared_counter{});
            }

            return *this;
        }


        inline bool const
        operator==(
            shared const& _other)
        {
            return this->operator ==(_other.get());
        }



        void release()
        {
            if(m_counter->alone())
            {
                this->destroy();
                m_counter.destroy();
            }

            else
                m_counter->decrease();
        }
    };


    template<
        typename type_t,
        typename ... args_t>
    shared<type_t>
    make_shared(
        args_t&&..._args)
    {
        return shared<type_t>{new type_t{perfect<args_t>(_args)...}};
    }


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


#endif /* ATOM_POINTERS_HPP_ */
