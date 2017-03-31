#include <iostream>
#include <exception>
#include <string>

#include <thodd/variant/variant.hpp>


int main () 
{
    thodd::variant<int, std::string> __v(12);
    std::cout << (int) __v << std::endl;
    __v = std::string("coucou");
    std::cout << (std::string) __v << std::endl;
}