#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <sstream>
#include <cstdint>
#include <fstream>

class Block
{
public:
    Block(Block *prev_block, const std::string &data, int difficulty);
    Block(std::ifstream &is, Block *prev_block);
    ~Block();

    std::string get_data() const;
    std::string get_hash() const;
    std::string get_prev_hash() const;
    Block *get_next_block() const;
    void set_next_block(Block *next_block);

    void serialize(std::ofstream &os) const;
    static Block *deserialize(std::ifstream &is, Block *prev_block);

private:
    std::string _data;
    std::string _hash;
    std::string _prev_hash;
    Block *_next_block;
    uint32_t _nonce;

    std::string calculate_hash();
    void mine_block(uint32_t difficulty);
};

#endif