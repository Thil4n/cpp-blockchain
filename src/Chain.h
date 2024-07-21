#ifndef CHAIN_H_INCLUDED
#define CHAIN_H_INCLUDED

#include "Block.h"
#include <cstdint>

class Chain
{
private:
    uint8_t _length;
    uint8_t _difficulty;
    Block *_current_block;
    Block *_genesis_block;

public:
    Chain();
    void set_difficulty(int difficulty);
    void append_data(std::string data);
    void print_chain() const;
    ~Chain();
};

#endif // CHAIN_H_INCLUDED
