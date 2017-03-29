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


template<
    typename ... params_t>
inline void
print_token(
    thodd::lang::basic_token<params_t...> const& __token, 
    auto&& __offset)
{
    if(static_cast<bool>(__token)) 
    {    
        std::cout << __offset << "|--> : ";

        for(auto&& __c : __token)
            std::cout << __c;

        std::cout << std::endl; 
    }
}


template<
    typename ... params_t>
inline void
print_token(
    thodd::lang::some_token<params_t...> const& __token, 
    auto&& __offset)
{
    if(static_cast<bool>(__token)) 
    {    
        std::cout << __offset << "|--> : ";

        for(auto&& __c : __token)
            std::cout << __c;

        std::cout << std::endl;

        for(auto&& __subtoken : __token.subranges)
            print_token(__subtoken, __offset + "___"); 
    }
}


template<
    typename ... params_t>
inline void
print_token(
    thodd::lang::follow_token<params_t...> const __token, 
    auto&& __offset)
{
    

    if(static_cast<bool>(__token))
    {    
        std::cout << __offset << "|--> : ";

        for(auto&& __c : __token)
            std::cout << __c;

        std::cout << std::endl;
        
        thodd::foreach(__token.subranges, [&__offset](auto&& __sub) {if(__sub != nullptr) print_token(*__sub, __offset + "___");});
    }
}

int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd;
    using namespace thodd::lang;

    std::string __input{"1116546545646"};
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

    constexpr auto __ds_word = __d_word >> __d_word >> *__d_word;
    

    auto __begin = __input.begin();
    auto __token = matches(__ds_word, __begin, __end);

    std::cout << std::boolalpha << (bool) __token << std::endl;

    
   // list<long long> __var = interpret(__ds_word, __token);
    
    print_token(__token, std::string());    
}
catch(std::exception& __e)
{
    std::cout << __e.what() << std::endl;
}