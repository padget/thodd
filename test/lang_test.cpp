#include <iostream>
#include <exception>

#include <string>

#include <thodd/lang.hpp>

extern constexpr auto __digit = 
    thodd::lang::make_regex(
        [] (auto& __cursor, 
            auto const& __end)
        {
            auto&& __res = '0' <= *__cursor 
                        && *__cursor <= '9';

            return __res ? 
                (++__cursor, true) : 
                false;
        });


extern constexpr auto __letter = 
    thodd::lang::make_regex(
        [] (auto& __cursor, 
            auto const& __end)
        {
            auto&& __res = 'a' <= *__cursor 
                        && *__cursor <= 'z';

            return __res ? 
                (++__cursor, true) : 
                false;
        });

inline void
print_tokens(
    auto&& __tree,
    auto&& __offset)
{
    std::cout << __offset 
              << "index : "     
              << __tree.index 
              << ':'; 

    for(auto&& __c : __tree)
        std::cout << __c;

    std::cout << " (" 
              << std::boolalpha 
              << __tree.valid 
              << ')';

    std::cout << std::endl;

    for(auto&& __token : __tree.subranges)
        print_tokens(__token, __offset + ' ');
}

int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd;
    using namespace thodd::lang;

    std::string __input{"1"};
    auto const __end = __input.end();

    constexpr auto 
    __d_word = 
        make_word(__digit)
        [
            ([](auto const& __token)
        {
            auto __unit = 1u;
            long long __res{0};

            for(auto&& __c : __token)
            {
                __res += (__c - '0') * __unit;
                __unit *= 10;
            }

            return __res;
        })];

    constexpr auto __ds_word = __d_word | __d_word;
    

    auto __begin = __input.begin();
    auto __token = matches(__ds_word, __begin, __end);

    std::cout << std::boolalpha << (bool) __token << std::endl;
    
    variant<long long> __var = interpret(__ds_word, __token);

    std::cout << static_cast<long long>(__var) << std::endl;
    
    print_tokens(__token, std::string());    
}
catch(std::exception& __e)
{
    std::cout << __e.what() << std::endl;
}