#ifndef __THODD_CORE_DESTROY_HPP__
#  define _THODD_CORE_DESTROY_HPP__

namespace
thodd 
{
    template<
        typename type_t>
    inline void
    destroy(
        type_t* _item)
    {
        delete _item;
        _item = nullptr;
    }
}

#endif