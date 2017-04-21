#include <iostream>
#include <string>

#include <thodd/variant/variant_proto.hpp>
#include <thodd/meta/traits/is_same.hpp>
#include <thodd/core/get.hpp>

static_assert(
    thodd::meta::is_same(
        thodd::meta::type_<thodd::proto::variant_unique<int, int>>{}, 
        thodd::meta::type_<thodd::proto::variant<int>>{}));

struct moto{};

int main()
{
    using namespace thodd::proto;

    variant<int, std::string> __v(113213);


    std::cout << __v.index() << std::endl;
    std::cout << thodd::get<int>(__v) << std::endl;

    __v = 25;

    std::cout << __v.index() << std::endl;
    std::cout << thodd::get<int>(__v) << std::endl;    
}