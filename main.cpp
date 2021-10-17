#include <tao/pegtl.hpp>
#include <iostream>

using namespace tao::pegtl;

int main() {
    std::cout << "Hello, World!" << std::endl;
    struct sign : one<'+', '-'> {
    };
    struct integer : seq<opt<sign>, plus<digit> > {
    };
    return 0;
}
