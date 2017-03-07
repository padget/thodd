#include <iostream>
#include <exception>

#include <thodd/meta/traits/is_same.hpp>


int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd::meta;
    using namespace thodd;

    std::cout << is_same(1,5);
}
catch(std::exception& e)
{

}