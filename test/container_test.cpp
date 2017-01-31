#include <exception>
#include <iostream>

#include <thodd/law.hpp>
#include <thodd/container_set.hpp>

#include <list>
class something
{
public:
    something(){std::cout << "default construction" << std::endl;}
    something(something const&){std::cout << "copy construction" << std::endl;}
    something(something&&){std::cout << "move construction" << std::endl;}
    something& operator = (something const&){std::cout << "copy equal" << std::endl;return *this;}
    something& operator = (something&&){std::cout << "move equal" << std::endl;return *this;}
    ~something(){std::cout << "destruction" << std::endl;}
};

constexpr auto
operator == (
    something const&, 
    something const&)
{
    return true;
}

int main(
    int argc, 
    char* args[])
try
{
    thodd::set<size_t> __ls{1, 2, 3, 3, 3};
    for(auto&& __item : __ls)
        std::cout << __item << std::endl;

}
catch(std::exception& __e)
{
    std::cerr << __e.what() << std::endl;
}