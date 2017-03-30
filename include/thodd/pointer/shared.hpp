#ifndef __THODD_POINTER_SHARED_HPP__
#  define __THODD_POINTER_SHARED_HPP__

#  include <thodd/pointer/handler.hpp>

namespace thodd
{
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
            m_counter{rvalue(_other.m_counter)} {}


        shared(
            shared&& _other):
            handler<type_t>{_other},
            m_counter{rvalue(_other.m_counter)} {}


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
            this->m_counter = rvalue(_other.m_counter);
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
                this->m_counter = rvalue(_other.m_counter);
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
}

#endif