#include <iostream>
#include <string>

#include <thodd/lang/regex/some.hpp>
#include <thodd/lang/regex/and.hpp>
#include <thodd/lang/regex/between.hpp>
#include <thodd/lang/regex/char_.hpp>
#include <thodd/lang/regex/not.hpp>
#include <thodd/lang/regex/or.hpp>
#include <thodd/lang/regex/regex.hpp>



int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd::lang::regex;
    std::string __s{"c"};
    
    auto __begin = __s.begin();
    auto __end = __s.end();

    std::cout << matches(chr('a'), __begin, __end) << '\n';
    --__begin;
    std::cout << matches(chr('c'), __begin, __end) << '\n' << std::endl;
}
catch(...)
{
}