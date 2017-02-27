#include <iostream>
#include <exception>

#include <thodd/functional.hpp>

#include <thodd/tuple.hpp>
#include <thodd/dynamic_tuple.hpp>

struct testref
{
    constexpr testref(){  }
    constexpr testref(testref const&){}
    constexpr testref(testref&&){ }
};

inline auto
operator << (auto& __out, testref const&)
-> decltype(auto)
{
    __out << "coucou";
    return __out;
}

int main(
    int argc,
    char* args[])
try
{
    using namespace thodd;
    
    {
        constexpr tuple<testref, testref, testref> __t{testref{}, testref{}, testref{}};
        constexpr decltype(__t) __t2(rvalue(__t));
        constexpr auto t = __t2 + __t2;
        thodd::foreach(t, cout_ << $0 << endl_);
    }

    std::cout << std::endl;

    {
        // dynamic_tuple<testref, testref, testref> __dt(testref{}, testref{}, testref{});
        // decltype(__dt) __dt2(rvalue(__dt));
        // __dt2 = __dt;
        // __dt2 = rvalue(__dt);
    }
}
catch(std::exception& __e)
{
    std::cout << __e.what() << std::endl;
}