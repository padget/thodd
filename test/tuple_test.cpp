#include <iostream>
#include <exception>

#include <thodd/functional/functional.hpp>

#include <thodd/tuple/tuple_element.hpp>
#include <thodd/tuple/tuple_indexed.hpp>
#include <thodd/tuple/tuple.hpp>
#include <thodd/tuple/dynamic_tuple.hpp>

struct testref
{
    constexpr testref() = default;
    constexpr testref(testref const&) { }
    constexpr testref(testref&&) { }
};

inline auto
operator << (auto& __out, testref const&)
-> decltype(auto)
{
    __out << "coucou";
    return __out;
}

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

    auto __t = {(__func(indexes_t), 0)...};
}


int main(
    int argc,
    char* args[])
try
{
    using namespace thodd;
    
    // thodd::foreach(
    //         thodd::extract<5, 8>(
    //             make_tuple(0,1,2,3,4,5,6,7,8,9)), 
    //         cout_ << $0 << endl_);
    
    // {
    //     constexpr tuple<testref, testref, testref> __t{testref{}, testref{}, testref{}};
    //     constexpr decltype(__t) __t2(rvalue(__t));
    //     constexpr auto t = __t2 + __t2;
    //     thodd::foreach(t, cout_ << $0 << endl_);
    //     std::cout << std::endl;
    //     thodd::foreach(
    //         thodd::extract<0, 5>(t), 
    //         cout_ << $0 << endl_);
    // }

    // std::cout << std::endl;

    // {
    //     dynamic_tuple<testref, testref, testref> __dt(testref{}, testref{}, testref{});
    //     decltype(__dt) __dt2(rvalue(__dt));
    //     __dt2 = __dt;
    //     __dt2 = rvalue(__dt);
    //     thodd::foreach(__dt2, cout_ << *$0 << endl_);
    // }

    // {
    //     thodd::tuple<>  __t;        
    // }

    {
        auto&& __t1 = make_tuple(1, 2, 3), __t2 = make_tuple(4,5,6), __t3 = make_tuple(7,8,9);
        thodd::foreach_join(
            cout_ << $0 << val(',') << $1 << val(',') << $2  << endl_, 
            __t1, __t2, __t3);
    }

    std::cout << std::endl;
  
}
catch(std::exception& __e)
{
    std::cout << __e.what() << std::endl;
}