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
    
    constexpr auto __c = 
        make_matcher(
        [](auto& __cursor, auto const& __end)
        {
            return *__cursor == 'c' ? (++__cursor, true) : false;
        });

     constexpr auto __d = 
        make_matcher(
        [](auto& __cursor, auto const& __end)
        {
            return *__cursor == 'd' ? (++__cursor, true) : false;
        });

    auto __ccccdcc_rule = make_rule((~__c)(4) >> __d >> __c >> __c);
    
    std::string str{"ccccdcc"};

    auto __begin = str.begin();
    auto __end = str.end();
    
    for(auto const& __item : matches(__ccccdcc_rule, __begin, __end))
        std::cout << __item;

    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
}