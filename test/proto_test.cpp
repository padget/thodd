#include <iostream>
#include <string>

#include <thodd/variant/variant_proto.hpp>
#include <thodd/meta/traits/is_same.hpp>

static_assert(
    thodd::meta::is_same(
        thodd::meta::type_<thodd::proto::variant_unique<int, int>>{}, 
        thodd::meta::type_<thodd::proto::variant<int>>{}));

int main()
{
    using namespace thodd::proto;

    variant<int, std::string> __v(2);

    std::cout << __v.index() << std::endl;
}