#include <exception>
#include <thodd/logging.hpp>
#include <thodd/functional.hpp> 



int main(
    int argc,
    char *argv[]) 
try
{
    using namespace thodd;
        
    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
}