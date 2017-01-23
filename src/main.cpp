#include <exception>
#include <thodd/logging.hpp>
#include <thodd/lang_new.hpp> 
#include <string>


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