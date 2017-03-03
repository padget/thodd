#include <iostream>
#include <exception>

#include <thodd/meta.hpp>
#include <thodd/law.hpp>

template<
    size_t ... idxs_c>
struct sequence {};

template<
    size_t max_c>
struct max {};

template<
    size_t min_c>
struct min {};


template<
    size_t max_c,
    size_t... indexes_c>
constexpr sequence<max_c, indexes_c...> 
make_sequence(
    sequence<max_c, indexes_c...>, 
    max<max_c>)
{
    return {};
}

template<
    size_t max_c,
    size_t ... nexts_c, 
    size_t index_c>
constexpr auto
make_sequence(
    sequence<index_c, nexts_c...>,
    max<max_c>)
{
    return 
    make_sequence(
        sequence<index_c + 1, index_c, nexts_c...>{}, 
        max<max_c>{});
}


template<
    size_t max_c>
constexpr auto
make_sequence(
    sequence<>,
    max<max_c>)
{
    return 
    make_sequence(
        sequence<0>{}, 
        max<max_c>{});
}

template<
    size_t ... indexes_c>
constexpr sequence<(sizeof...(indexes_c) - 1 - indexes_c)...>
revert_sequence(
    sequence<indexes_c...>)
{
    return {};
}


template<
    size_t min_c, 
    size_t max_c>
constexpr auto
make_sequence(
    min<min_c>, 
    max<max_c>)



template<
    size_t ... idx>
void
print_sequence(
    sequence<idx...>)
{
    thodd::repeat{((std::cout << idx), 0)...};
}

int main(
    int argc, 
    char* args[])
try
{
    print_sequence(revert_sequence(make_sequence(sequence<>{}, max<20>{})));
}
catch(std::exception& e)
{

}