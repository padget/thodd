#ifndef __THODD_LANG_CORE_HPP__
#  define __THODD_LANG_CORE_HPP__

namespace thodd
{
    namespace lang
    {
        template<
            typename type_t>
        using __target = typename type_t::target;
    }
}

#endif