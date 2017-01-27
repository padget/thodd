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

    auto __c_rule = make_rule(__c);
    auto __d_rule = make_rule(__d);

    //auto __c_or_d_rule = __c_rule | __d_rule;
    auto __c_and_d_rule = __c_rule >> __d_rule;
    
    std::string str{"ecccdcc"};

    auto __begin = str.begin();
    auto __end = str.end();
    
    auto __res = matches(__c_and_d_rule, __begin, __end);

    std::cout << __res.subranges.size() << std::endl;

//    for(auto const& __item : __res)
//         std::cout << __item;

    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
}