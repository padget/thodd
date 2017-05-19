#include <exception>
#include <iostream>

#include <thodd/container/tree.hpp>

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


int main(
    int argc, 
    char* args[])
try
{
    using namespace thodd;

    tree_node<int> __root{1};
    tree_node<int> __2{2};
    tree_node<int> __21{21};
    tree_node<int> __22{22};
    
    auto& __2in = *__root.childs.push_at(__2, __root.childs.end());
    __2in.parent = &__root;

    auto& __21in = *__root.childs.push_at(__21, __root.childs.end());
    __21in.parent         = &__root;
    __2in.great_brother   = &__21in;
    __21in.little_brother = &__2in;
    
    auto& __22in = *__root.childs.push_at(__22, __root.childs.end());
    __22in.parent         = &__root;
    __21in.great_brother  = &__22in;
    __22in.little_brother = &__21in;

    rlg_tree_iterator<int> const __it{&__root};

    std::cout << *__it << std::endl;
    std::cout << *++__it << std::endl;
    std::cout << *++__it << std::endl;
    std::cout << *++__it << std::endl;
}
catch(std::exception& __e)
{
    std::cerr << __e.what() << std::endl;
}