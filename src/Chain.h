#ifndef CHAIN_H
#define CHAIN_H

#include "Block.h"
#include <string>

class Chain
{
public:
    Chain();
    ~Chain();

    void set_difficulty(int difficulty);
    void append_data(const std::string &data);
    void print_chain() const;
    void save_chain(const std::string &filename) const;
    void load_chain(const std::string &filename);

private:
    Block *_genesis_block;
    Block *_current_block;
    int _difficulty;
    int _length;

    void create_genesis_block();
};

#endif