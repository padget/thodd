#ifndef __THODD_META_TYPE_HPP__
#  define __THODD_META_TYPE_HPP__ 

namespace 
thodd::meta
{
    template<
        typename type_t>
    using __type = typename type_t::type;

    template<
        typename type_t>
    struct type_
    {
        using type = type_t;
    };
}

#endif