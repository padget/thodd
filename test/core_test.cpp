#include <iostream>
#include <exception>

#include <thodd/core/rvalue.hpp>
#include <thodd/core/perfect.hpp>
#include <thodd/core/sequence.hpp>
#include <thodd/core/integral.hpp>
#include <thodd/core/expand.hpp>

struct test
{
    test() { std::cout << "build" << std::endl;}
    test(test const&) { std::cout << "copy" << std::endl;}
    test(test&&) { std::cout << "move" << std::endl;}
    ~test() { std::cout << "destroy" << std::endl;}
};

template<
    typename type_t, 
    template<typename, type_t...> typename sequence_t, 
    type_t ... indexes_t>
constexpr auto
foreach(
    sequence_t<type_t, indexes_t...> const&, 
    auto&& __func)
{
    using namespace thodd;

    expand((__func(indexes_t), 0)...);
}

int main()
try
{
    using namespace thodd;

    test __t2{perfect(test{})};
    foreach(reverse_sequence(make_sequence(iint_<12>{})), [](auto&& __item){ std::cout << __item; });   
}
catch (std::exception& e)
{
    std::cerr << e.what() << std::endl;
}