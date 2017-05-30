#include <iostream>
#include <string>

constexpr long double operator""_deg ( int deg )
{
    return deg*3.141592/180;
}

int main()
{
    auto i = 2_deg;
    std::cout << i << std::endl;
    return 0;
}