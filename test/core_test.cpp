#include <iostream>
#include <exception>

#include <thodd/core/rvalue.hpp>
#include <thodd/core/perfect.hpp>

struct test
{
    test() { std::cout << "build" << std::endl;}
    test(test const&) { std::cout << "copy" << std::endl;}
    test(test&&) { std::cout << "move" << std::endl;}
    ~test() { std::cout << "destroy" << std::endl;}
};

int main()
try
{
    test __t2{thodd::perfect(test{})};
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
}