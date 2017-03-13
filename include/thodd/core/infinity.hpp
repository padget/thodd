#ifndef __THODD_CORE_INFINITE_HPP__
#  define __THODD_CORE_INFINITE_HPP__

#  include <limits>
#  include <thodd/core/size_t.hpp>

namespace 
thodd
{
    extern constexpr size_t infinity = 
        std::numeric_limits<size_t>::max();
}

#endif