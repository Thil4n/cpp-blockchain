#include "Chain.h"

#include <iostream>

int main()
{

    Chain chain;
    chain.set_difficulty(1);

    chain.append_data("Block 1 Data");
    chain.append_data("Block 2 Data");

    chain.save_chain("blockchain.dat");

    Chain loaded_chain;
    loaded_chain.load_chain("blockchain.dat");

    loaded_chain.print_chain();

    return 0;
}