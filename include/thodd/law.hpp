#ifndef THODD_LAW_HPP_
#  define THODD_LAW_HPP_

#  include <thodd/meta.hpp>
#  include <initializer_list>
#  include <limits>

#  define THODD_EXCEPTION(name, message)                             \
    class name :                                                    \
        public std::exception                                        \
    {                                                                \
    public:                                                            \
        virtual char const* what() const noexcept{return message;}    \
    };                                                                \


namespace thodd
{
    using boolean = bool;
    using size_t  = unsigned long long;
    using point_t = long long;

    template<
        typename type_t>
    inline void
    destroy(
        type_t* _item)
    {
        delete _item;
        _item = nullptr;
    }


    constexpr size_t infinity = std::numeric_limits<size_t>::max();

 
    template<
        typename type_t>
    constexpr type_t&&
    perfect(
        meta::remove_reference<type_t>& __t) noexcept
    {
        return static_cast<type_t&&>(__t);
    }


    template<
        typename type_t>
    constexpr type_t&&
    perfect(
        meta::remove_reference<type_t>&& __t) noexcept
    {
        return static_cast<type_t&&>(__t);
    }    


    template<
        typename type_t>
    constexpr meta::remove_reference<type_t>&&
    rvalue(
        type_t&& arg) noexcept
    {
        return static_cast<meta::remove_reference<type_t>&&>(arg);
    }


    template<
        typename type_t>
    struct __declval_protector
    {
        static const bool __stop = false;
        static meta::add_rvalue_reference<type_t> __delegate();
    };



    template<
        typename type_t>
    inline meta::add_rvalue_reference<type_t>
    declval() noexcept
    {
        static_assert(
            __declval_protector<type_t>::__stop,
            "declval() must not be used!");
        return __declval_protector<type_t>::__delegate();
    }



    using repeat = std::initializer_list<int>;
}

#endif /* THODD_LAW_HPP_ */
