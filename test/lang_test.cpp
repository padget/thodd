#include <iostream>
#include <exception>

#include <string>
// #include <type_traits>
#include <thodd/meta/traits/is_base_of.hpp>
#include <thodd/meta/traits/decay.hpp>
#include <thodd/meta/type.hpp>

struct regex_base
{
    constexpr auto
    operator() ()
    {
        return 3;
    }
} ;

struct regex : 
    regex_base
{

} ;

struct bad_regex 
{

} ;

constexpr auto 
operator ~ (
    auto&& __r)
{
    using namespace thodd::meta ;

    static_assert(
        is_base_of(
            type_<regex_base>{}, 
            type_<decay_t<decltype(__r)>>{}), 
        "not based on regex_base") ;

    return __r ;
}

int main(
    int argc, 
    char* args[])
try
{
    constexpr bad_regex __r {};
    std::cout << (~__r)() << std::endl;

}
catch( ... )
{
    std::cout << "something happened bad" << std::endl;
}