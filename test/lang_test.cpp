#include <iostream>
#include <exception>

#include <string>

#include <thodd/lang.hpp>

enum class calc
{
    integer,
    comma, 
    lbracket, 
    rbracket, 
    plus, 
    minus, 
    multiply, 
    divide
};


auto operator ""_xa (auto i)
{
    return 
    (int) i;
}


int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd;
    using namespace thodd::lang;

    std::string __input = "d";
    
    auto __begin = __input.begin();
    auto __end = __input.end();

    std::cout << 2_xa << std::endl;   

    std::cout << "endl" << std::endl;

}
catch( ... )
{
    std::cout << "something happened bad" << std::endl;
}