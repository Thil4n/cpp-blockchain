#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <openssl/sha.h>
#include <cstdint>
#include <cstring>
#include <cstdio>

class Block
{
private:
    uint8_t _hash[SHA256_DIGEST_LENGTH];
    uint8_t _prev_hash[SHA256_DIGEST_LENGTH];

    uint8_t *_data;
    uint8_t _data_size;

    uint8_t _nonce;

    Block *_next_block;

public:
    Block(Block *_prev_block, const uint8_t *data, uint8_t data_size);

    uint8_t *get_hash();
    const uint8_t *get_prev_hash();

    Block *get_next_block();
    void set_next_block(Block *next_block);

    void calculate_hash();
    char *get_hash_str();
    bool is_difficulty();
    void mine_block();

    ~Block();
};

#endif // BLOCK_H_INCLUDED