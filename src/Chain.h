#ifndef CHAIN_H_INCLUDED
#define CHAIN_H_INCLUDED

#include "Block.h"
#include <cstdint>

class Chain
{
private:
    uint8_t _length;
    Block *_current_block;
    Block *_genesis_block;

public:
    Chain();
    void append_data(const uint8_t *data, uint8_t size);
    void print_chain() const;
    ~Chain();
};

#endif // CHAIN_H_INCLUDED
