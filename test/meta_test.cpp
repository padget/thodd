#include <iostream>
#include <exception>

#include <thodd/meta.hpp>
#include <thodd/law.hpp>

#include <thodd/core_sequence.hpp>
#include <thodd/functional.hpp>


template<
    size_t ... idx>
void
print_sequence(
    thodd::meta::sequence<idx...>)
{
    thodd::repeat{((std::cout << idx << std::endl), 0)...};
}

int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd::meta;
    using namespace thodd;

    print_sequence(
        reverse_sequence(
        make_sequence(
            max<12>{}, 
            [] (auto __i) { return __i + 2; } 
        ))
    );
}
catch(std::exception& e)
{

}