#include <exception>
#include <thodd/logging.hpp>
#include <thodd/properties.hpp>
#include <string>

int main(
    int argc,
    char *argv[]) 
try
{
    using namespace thodd;
    using namespace thodd::lang;
    using namespace thodd::contdsl;

    logger<root>::info("########## ATOM Launched ##########");

    std::string __str {"un= deux"};
    
    parse_property(__str.begin(), __str.end());

    logger<root>::info("########## ATOM Stopped ##########");

    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
}