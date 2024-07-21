#include <iostream>
#include "Chain.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Chain new_chain = Chain();
    new_chain.set_difficulty(1);

    new_chain.append_data("hello");
    new_chain.append_data("sdf");
    new_chain.append_data("hello");
    new_chain.append_data("hello");

    new_chain.print_chain();

    return 0;
}
