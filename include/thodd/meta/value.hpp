#ifndef __THODD_META_VALUE_HPP__
#  define __THODD_META_VALUE_HPP__

namespace 
thodd::meta
{
    template<
        typename value_t,
        value_t value_c>
    struct value_
    {
        using value_type = value_t;
        static constexpr value_t value{value_c};

        constexpr auto
        operator () () const
        {
            return value;
        }
    };


    template<
        typename type_t>
    using __value_type = typename type_t::value_type;
}

#endif