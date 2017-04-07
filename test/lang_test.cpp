#include <iostream>
#include <exception>

#include <string>

#include <thodd/lang.hpp>
#include <thodd/container/dsl.hpp>

extern constexpr auto __digit = 
    thodd::lang::make_regex(
        [] (auto& __cursor, 
            auto const& __end)
        {
            auto&& __res = '0' <= *__cursor 
                        && *__cursor <= '9';

            std::cout << (__res ? *__cursor : '.') << std::endl; 

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

            std::cout << (__res ? *__cursor : '.') << std::endl;

            return __res ? 
                (++__cursor, true) : 
                false;
        });

template<
    typename ... params_t>
inline void
print_token(
    thodd::lang::basic_token<params_t...> const& __token, 
    auto&& __offset);

template<
    typename ... params_t>
inline void
print_token(
    thodd::lang::follow_token<params_t...> const& __token, 
    auto&& __offset);

template<
    typename ... params_t>
inline void
print_token(
    thodd::lang::follow_token<params_t...> const& __token, 
    auto&& __offset);

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

        for(auto const& __subtoken : __token.subranges)
            print_token(__subtoken, __offset + "___"); 
    }
}


template<
    typename ... params_t>
inline void
print_token(
    thodd::lang::follow_token<params_t...> const& __token, 
    auto&& __offset)
{
    if(static_cast<bool>(__token))
    {    
        std::cout << __offset << "|--> : ";

        for(auto&& __c : __token)
            std::cout << __c;

        std::cout << std::endl;
        
        thodd::foreach(
            __token.subranges, 
            [&__offset] 
            (auto const& __sub) 
            {
                if(__sub != nullptr) 
                    print_token(*__sub, __offset + "___");
            });
    }
}

// detect a digit
constexpr auto __d_word = make_word(__digit) ;
constexpr auto __l_word = make_word(__letter) ;

constexpr auto __ds_word = * ((*__l_word >> *__d_word)[(cout_ << "coucou" << endl_, $0)]);
constexpr auto __ds_wordf = __l_word >> __d_word;


int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd;
    using namespace thodd::lang;

    std::string __input{"a1a1a1a1a1a1a1aaaa1111aaaa2222"};
    auto const __end = __input.end();
       
    auto __begin = __input.begin();
    auto __token = matches(__ds_word, __begin, __end);
    print_token(__token, std::string()); 

    auto __var = interpret(__ds_word, __token);
    auto sum = 0;
    sum ++; 
   
    // for(auto&& __item : __var)
    //     print_token(__item, "__");
}
catch( ... )
{
    std::cout << "something happened bad" << std::endl;
}