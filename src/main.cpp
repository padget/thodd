#include <exception>
#include <thodd/functional_lambda.hpp> 


int main(
    int argc,
    char *argv[]) 
try
{
    using namespace thodd;
    ;
    auto __cpt = 1u;

    std::cout << 
    tern($0 == val(0u)) [ 
        cout_ << val(2),
        val('0') 
    ][ 
        cout_ << val(0),
        val('c')
    ](2) ;

    return 0;
}
catch (std::exception &e)
{
    std::cerr << e.what() << std::endl;
}