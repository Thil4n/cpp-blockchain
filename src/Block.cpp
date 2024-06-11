#include "Block.h"
#include <unistd.h>

#include <iostream>

using namespace std;

Block::Block(Block *prev_block, const uint8_t *data, uint8_t data_size)

{

    _data_size = data_size;
    _next_block = nullptr;

    if (prev_block == NULL) // This is genesis block
    {
        memset(_prev_hash, 0, SHA256_DIGEST_LENGTH); // set _prev_hash to null
    }
    else
    {
        // Copy previous block's hash to _prev_hash
        memcpy(_prev_hash, prev_block->get_hash(), SHA256_DIGEST_LENGTH);
        prev_block->set_next_block(this);
    }

    _data = new uint8_t[data_size];
    memcpy(_data, data, data_size);

    calculate_hash();
    mine_block();
}

uint8_t *Block::get_hash()
{
    return _hash;
}

const uint8_t *Block::get_prev_hash()
{
    return _prev_hash;
}

void Block::set_next_block(Block *next_block)
{
    _next_block = next_block;
}

Block *Block::get_next_block()
{
    return _next_block;
}

void Block::calculate_hash()
{
    uint32_t sz = SHA256_DIGEST_LENGTH + _data_size + sizeof(uint8_t);
    uint8_t *buf = new uint8_t[sz];
    uint8_t *ptr = buf;

    memcpy(ptr, _prev_hash, SHA256_DIGEST_LENGTH);
    ptr += SHA256_DIGEST_LENGTH;

    if (_data_size != 0)
    {
        memcpy(ptr, _data, _data_size);
    }

    memcpy(ptr, &_nonce, sizeof(uint32_t));
    ptr += sizeof(uint32_t);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, buf, sz);
    SHA256_Final(_hash, &sha256);

    delete[] buf;
}

char *Block::get_hash_str()
{
    char *buf = new char[SHA256_DIGEST_LENGTH * 2 + 1];
    for (uint32_t n = 0; n < SHA256_DIGEST_LENGTH; n++)
    {
        sprintf(buf + n * 2, "%02x", _hash[n]);
    }
    buf[SHA256_DIGEST_LENGTH * 2] = 0;
    return buf;
}

bool Block::is_difficulty()
{
    cout << get_hash_str()[0] << endl;

    for (uint8_t n = 0; n < 1; n++)
    {
        if (get_hash_str()[n] != 60)
            return false;
    }
    return true;
}

void Block::mine_block()
{
    _nonce = 0;

    while (!is_difficulty())
    {
        _nonce++;
        calculate_hash();
        usleep(10);
    }
}

Block::~Block()
{
    delete[] _data;
}