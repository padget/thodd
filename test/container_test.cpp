#include <exception>
#include <iostream>


#include <thodd/container/list.hpp>

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
    thodd::list<int> __ls{1,2,3,4,5,6};

    auto __vs = thodd::view(__ls);

    for(auto&& __item : __vs)
        std::cout << __item << std::endl;

    for(auto& __item : __ls)
        __item++;

    for(auto&& __item : __vs)
        std::cout << __item << std::endl;

}
catch(std::exception& __e)
{
    std::cerr << __e.what() << std::endl;
}