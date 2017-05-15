#include <exception>
#include <thodd/logging.hpp>
#include <thodd/lang.hpp> 
#include <string>

struct __test
{
    void get() & 
    {
        std::cout << "&" << std::endl;
    }


    void get() const &
    {
        std::cout << "const &" << std::endl;
    }


    void get() &&
    {
        std::cout << "&&" << std::endl;
    }
};

void foo(auto&& __t)
{
    using namespace thodd;

    perfect<decltype(__t)>(__t).get();
}

void foo2(__test&& __t)
{
    using namespace thodd;
    
    __t.get();
}


int main(
    int argc,
    char *argv[]) 
try
{
    using namespace thodd;
    using namespace thodd::lang;    


    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
}