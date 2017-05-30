#ifndef __THODD_POINTER_HANDLER_HPP__
#  define __THODD_POINTER_HANDLER_HPP__

#  include <thodd/core/rvalue.hpp>
#  include <thodd/core/perfect.hpp>
#  include <thodd/core/exception.hpp>
#  include <thodd/core/destroy.hpp>

#  include <thodd/require.hpp>
#  include <thodd/functional/functional.hpp>

namespace thodd
{
    THODD_EXCEPTION(
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
            m_handled{rvalue(_other.m_handled)} {}


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
            reset(rvalue(_other.m_handled));
            return *this;
        }


    public:
        type_t*
        get() 
        {
            return m_handled;
        }


        type_t const*
        get() const
        {
            return m_handled;
        }


        type_t*
        operator -> ()
        {
            return m_handled;
        }


        type_t const*
        operator -> () const
        {
            return m_handled;
        }


        type_t&
        operator * ()
        {
            go<contract>(
                require(ref(m_handled) != val(nullptr))
                > throw_<null_pointer_exception>());

            return *m_handled;
        }


        type_t const&
        operator * () const
        {
            go<contract>(
                require(ref(m_handled) != val(nullptr))
                > throw_<null_pointer_exception>());

            return *m_handled;
        }

       
        inline type_t&
        operator [] (
            size_t const& _index)
        {
            go<contract>(
                require(!*ref(this)) 
                > throw_<null_pointer_exception>());

            return *(m_handled + _index);
        }


        inline type_t const&
        operator [] ( 
            size_t const& _index) const
        {
            go<contract>(
                require(!*ref(this)) 
                > throw_<null_pointer_exception>());
           
            return *(m_handled + _index);
        }


        inline bool const
        operator == (
            type_t* _other) const
        {
            return m_handled == _other;
        }


        inline bool const
        operator == ( 
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
}

#endif