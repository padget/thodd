#include <iostream>
#include <exception>

#include <thodd/functional.hpp>

#include <thodd/tuple.hpp>
#include <thodd/dynamic_tuple.hpp>

struct testref
{
    testref(){ std::cout << "constructor" << std::endl; }
    ~testref(){ std::cout << "destructor" << std::endl; }
    testref(testref const&){ std::cout << "copy constructor" << std::endl; }
    testref(testref&&){ std::cout << "move constructor" << std::endl; }
    testref& operator = (testref const&){ std::cout << "copy assignement" << std::endl; return *this; }
    testref& operator = (testref&&){ std::cout << "move assignement" << std::endl;  return *this; }
};

int main(
    int argc,
    char* args[])
try
{
    using namespace thodd;
    
    {
        tuple<testref, testref, testref> __t{testref{}, testref{}, testref{}};
        decltype(__t) __t2(rvalue(__t));
        __t2 = __t;
        __t2 = rvalue(__t);
        auto t = __t2 +__t2;
    }

    std::cout << std::endl;

    {
        dynamic_tuple<testref, testref, testref> __dt(testref{}, testref{}, testref{});
        decltype(__dt) __dt2(rvalue(__dt));
        __dt2 = __dt;
        __dt2 = rvalue(__dt);
    }

    std::cout << std::endl;

    {
        dynamic_tuple<testref> __dt{testref{}};
        dynamic_tuple<int> __dt2{2};
        auto __sum = __dt + __dt2;
    }
}
catch(std::exception& __e)
{
    std::cout << __e.what() << std::endl;
}