#include <exception>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

#include <thodd/containers.hpp>
#include <thodd/logging.hpp>
#include <thodd/lang.hpp>
#include <thodd/variant.hpp>
#include <thodd/string.hpp>


int main(
    int argc,
    char *argv[]) 
try
{
    using namespace thodd;
    using namespace thodd::lang;
    using namespace thodd::contdsl;

    

    logger<root>::info("########## ATOM Launched ##########");
    constexpr auto __tmp = {1,2,3,4,5,6,7,8,9};

    go<query>(
        with($0) > foreach(cout_ << $0 << endl_), 
        __tmp);

    logger<root>::info("########## ATOM Stopped ##########");

    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
}