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

    foo(__test{});
    auto __t = __test{};

    foo2(__test{});
    rvalue(__t).get();


//     constexpr auto __c = 
//         make_regex(
//         [](auto& __cursor, auto const& __end)
//         {
//             return *__cursor == 'c' ? (++__cursor, true) : false;
//         });

//      constexpr auto __d = 
//         make_regex(
//         [](auto& __cursor, auto const& __end)
//         {
//             return *__cursor == 'd' ? (++__cursor, true) : false;
//         });

//     auto __c_word = make_word(__c);
//     auto __d_word = make_word(__d);

//     //auto __c_or_d_word = __c_word | __d_word;
//     auto __c_and_d_word = __c_word >> __d_word;
    
//     std::string str{"ecccdcc"};

//     auto __begin = str.begin();
//     auto __end = str.end();
    
//     auto __res = matches(__c_and_d_word, __begin, __end);

//     std::cout << __res.subranges.size() << std::endl;

// //    for(auto const& __item : __res)
// //         std::cout << __item;

    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
}