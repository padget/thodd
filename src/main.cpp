#include <exception>
#include <thodd/logging.hpp>
#include <thodd/lang.hpp> 
#include <string>


int main(
    int argc,
    char *argv[]) 
try
{
    using namespace thodd;
    using namespace thodd::lang;    
    
    std::string __str = {"c"};
    
    auto __cursor = __str.begin();
    auto __end    = __str.end();
    
    std::cout << matcher::sym('c')(__cursor, __end);

    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
}