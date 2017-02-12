#include <iostream>
#include <exception>

#include <string>

#include <thodd/lang.hpp>

extern constexpr auto __digit = 
    thodd::lang::make_matcher(
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
    thodd::lang::make_matcher(
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
    
    std::cout << __offset << "id : " << __tree.id << std::endl;

    for(auto&& __token : __tree.subranges)
        print_tokens(__token, __offset+=' ');
}

int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd;
    using namespace thodd::lang;

    std::string __input{"111"};
    auto const __end = __input.end();
    auto __dol_word = *make_word(__digit);
    
    std::cout << "min : " << __dol_word.algo.min << std::endl;
    std::cout << "max : " << __dol_word.algo.max << std::endl;

    auto __begin2 = __input.begin();
    auto __tree = matches(__dol_word, __begin2, __end);

    print_tokens(__tree, std::string());
}
catch(std::exception& __e)
{
    std::cout << __e.what() << std::endl;
}