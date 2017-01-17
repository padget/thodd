#ifndef __THODD_PROPERTIES_HPP__
#  define __THODD_PROPERTIES_HPP__

#  include <thodd/lang.hpp>
#  include <thodd/string.hpp>
#  include <thodd/containers.hpp>

namespace thodd
{
    template<
        typename iterator_t>
    inline void 
    parse_property(
        iterator_t __begin, 
        iterator_t const __end)
    {
        using namespace lang::parser;

        constexpr auto lower = range('a', 'z');
        
        constexpr auto point = sym('.');
        constexpr auto equal = sym('=');
        constexpr auto space = sym(' ');

        constexpr auto key = +(+lower >> (~point)(0, 1));
        constexpr auto value = +(+lower >> *space);

        constexpr auto prop = key >> equal >> value;
        auto __res = prop.attr();

        std::cout << typeid(__res).name() << std::endl;
        std::cout << std::boolalpha << prop(__begin, __end) << std::endl; 
    }

    
    struct property
    {
        string key;
        string value;
    };

    struct properties
    {
        list<property> data;
    };
}

#endif