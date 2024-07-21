#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <cstdint>
#include <iostream>
#include <sstream>

class Block
{
private:
    std::string _hash;
    std::string _prev_hash;

    std::string _data;

    uint8_t _nonce;

    Block *_next_block;

public:
    Block(Block *_prev_block, std::string data, int difficulty);

    std::string get_hash();
    std::string get_prev_hash();

    Block *get_next_block();
    void set_next_block(Block *next_block);

    std::string calculate_hash();
    bool is_difficulty();
    void mine_block(uint32_t difficulty);

    ~Block();
};

#endif // BLOCK_H_INCLUDED