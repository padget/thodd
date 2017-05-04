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
    thodd::lang::token<params_t...> const& __token, 
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
    thodd::lang::token<params_t...> const& __token, 
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


template<
    typename ... params_t>
inline void
print_token(
    thodd::lang::alternative_token<params_t...> const& __token, 
    auto&& __offset)
{
    if(static_cast<bool>(__token))
    {    
        std::cout << __offset << "|--> : " << '(' << __token.index << ')';
        
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
constexpr auto __d_word = make_word(__digit);
constexpr auto __l_word = make_word(__letter);

constexpr auto some_exec = (thodd::cout_ << thodd::val(1234) << thodd::endl_, thodd::$0);

constexpr auto __ds_word = *((*__l_word >> *__d_word)[some_exec]);
    
constexpr auto __ds_wordf = __l_word >> __d_word;


int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd;
    using namespace thodd::lang;

    std::string __input2 = "d";
    auto __begin2 = __input2.begin();
    constexpr auto __ords = __d_word | __l_word;

    auto __token2 = matches(__ords, __begin2, __input2.end());

    print_token(__token2, std::string());
    std::cout << "endl" << std::endl;

}
catch( ... )
{
    std::cout << "something happened bad" << std::endl;
}