#include "Block.h"
#include "sha256.h"
#include <unistd.h>

using namespace std;

Block::Block(Block *prev_block, string data, int difficulty)

{

    _next_block = nullptr;

    if (prev_block != NULL)

    {
        // Copy previous block's hash to _prev_hash
        _prev_hash = prev_block->get_hash();
        prev_block->set_next_block(this);
    }

    _data = data;

    calculate_hash();
    mine_block(difficulty);
}

string Block::get_hash()
{
    return _hash;
}

string Block::get_prev_hash()
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

inline string Block::calculate_hash()
{
    stringstream ss;
    ss << _prev_hash << _data << _nonce;

    return sha256(ss.str());
}

void Block::mine_block(uint32_t difficulty)
{
    char cstr[difficulty + 1];
    for (uint32_t i = 0; i < difficulty; ++i)
    {
        cstr[i] = '0';
    }
    cstr[difficulty] = '\0';

    string str(cstr);

    do
    {
        _nonce++;
        _hash = calculate_hash();

    } while (_hash.substr(0, difficulty) != str);

    cout << "Block mined: " << _hash << endl;
}

Block::~Block()
{
}