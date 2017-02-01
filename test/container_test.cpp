#include <exception>
#include <iostream>

#include <thodd/law.hpp>
#include <thodd/container_map.hpp>

#include <list>
class something
{
public:
    something(){std::cout << "default construction" << std::endl;}
    something(something const&){std::cout << "copy construction" << std::endl;}
    something(something&&){std::cout << "move construction" << std::endl;}
    something& operator = (something const&){std::cout << "copy equal" << std::endl;return *this;}
    something& operator = (something&&){std::cout << "move equal" << std::endl;return *this;}
    ~something(){std::cout << "destruction" << std::endl;}
};

constexpr auto
operator == (
    something const&, 
    something const&)
{
    return true;
}


template<typename key_t, typename value_t>
std::ostream& 
operator << (
    std::ostream& __out, thodd::entry<key_t, value_t> const& __entry)
{
    return (__out << __entry.key << ' ' << __entry.value);
}

int main(
    int argc, 
    char* args[])
try
{
    thodd::map<int, int> __ls{thodd::entry<int, int>{1, 2}, thodd::entry<int, int>{3, 4}, thodd::entry<int, int>{1, 2}};
    for(auto&& __item : __ls)
        std::cout << __item << std::endl;

}
catch(std::exception& __e)
{
    std::cerr << __e.what() << std::endl;
}