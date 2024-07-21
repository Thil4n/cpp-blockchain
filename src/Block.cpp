#include "Block.h"
#include "sha256.h"
#include <iostream>
#include <sstream>

using namespace std;

Block::Block(Block *prev_block, const string &data, int difficulty)
    : _data(data), _next_block(nullptr), _nonce(0)
{
    if (prev_block == nullptr)
    {
        _prev_hash = string(64, '0');
    }
    else
    {
        _prev_hash = prev_block->get_hash();
        prev_block->set_next_block(this);
    }
    calculate_hash();
    mine_block(difficulty);
}

Block::Block(ifstream &is, Block *prev_block) : _next_block(nullptr)
{
    string line;
    getline(is, line);
    if (line.empty())
        return;

    stringstream ss(line);
    getline(ss, _prev_hash, ' ');
    getline(ss, _hash, ' ');
    getline(ss, _data, '`'); // Skip leading quote
    getline(ss, _data, '`'); // Read data till closing quote
    ss >> _nonce;

    if (prev_block == nullptr)
    {
        _prev_hash = string(64, '0');
    }
    else
    {
        prev_block->set_next_block(this);
    }
}

string Block::get_data() const
{
    return _data;
}

string Block::get_hash() const
{
    return _hash;
}

string Block::get_prev_hash() const
{
    return _prev_hash;
}

void Block::set_next_block(Block *next_block)
{
    _next_block = next_block;
}

Block *Block::get_next_block() const
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
    string str(difficulty, '0');

    do
    {
        _nonce++;
        _hash = calculate_hash();
    } while (_hash.substr(0, difficulty) != str);

    cout << "Block mined: " << _hash << endl;
}

void Block::serialize(ofstream &os) const
{

    os << _prev_hash << " " << _hash << " `" << _data << "` " << _nonce << "\n";
}

Block *Block::deserialize(ifstream &is, Block *prev_block)
{
    return new Block(is, prev_block);
}

Block::~Block()
{
    // No dynamic memory allocation here, so nothing special needed
}