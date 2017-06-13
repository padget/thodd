#include <thodd/lang/regex/some.hpp>
#include <thodd/lang/regex/and.hpp>
#include <thodd/lang/regex/between.hpp>
#include <thodd/lang/regex/char_.hpp>
#include <thodd/lang/regex/not.hpp>
#include <thodd/lang/regex/or.hpp>
#include <thodd/lang/regex/regex.hpp>

constexpr bool
matches(
    between<auto, auto> const& __between, 
    auto const& __c)
{
    return 
}

int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd::lang::regex;
    
    (!((chr('A') - chr('Z')) > (chr('A') - chr('Z')) > *(chr('a') - chr('z')))) | +(chr('0') - chr('9')) | !chr('a');
}
catch(...)
{
}