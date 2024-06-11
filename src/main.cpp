#include <iostream>
#include "Chain.h"

using namespace std;

int main(int argc, char const *argv[])
{

    Chain new_chain = Chain();

    uint8_t *garbage = new uint8_t[32];
    for (uint32_t n = 0; n < 32; n++)
        garbage[n] = clock() % 255;

    new_chain.append_data(garbage, 32);
    new_chain.append_data(garbage, 32);
    new_chain.append_data(garbage, 32);
    new_chain.append_data(garbage, 32);
    new_chain.append_data(garbage, 32);
    new_chain.print_chain();

    return 0;
}
