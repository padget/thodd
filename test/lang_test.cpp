#include <iostream>
#include <exception>

#include <thodd/lang.hpp>

int main(
    int argc, 
    char* args[])
try
{

}
catch(std::exception& __e)
{
    std::cout << __e.what() << std::endl;
}