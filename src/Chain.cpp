#include "Chain.h"
#include <iostream>
#include <fstream>

using namespace std;

Chain::Chain()
    : _difficulty(1), // Initialize difficulty with a realistic value
      _length(0),
      _current_block(nullptr),
      _genesis_block(nullptr)
{
    // Genesis block creation moved to create_genesis_block method
}

void Chain::set_difficulty(int difficulty)
{
    _difficulty = difficulty;
}

void Chain::create_genesis_block()
{
    if (_genesis_block == nullptr)
    {
        _current_block = new Block(nullptr, "Genesis Block", _difficulty);
        _genesis_block = _current_block;
        _length++;
    }
}

void Chain::append_data(const std::string &data)
{
    if (_genesis_block == nullptr)
    {
        create_genesis_block();
    }

    Block *new_block = new Block(_current_block, data, _difficulty);
    _current_block = new_block;
    _length++;
}

void Chain::print_chain() const
{
    Block *temp = _genesis_block;
    int block_num = 0;

    while (temp != nullptr)
    {
        cout << "Block " << block_num << ": " << temp->get_data() << endl;
        temp = temp->get_next_block();
        block_num++;
    }
}

void Chain::save_chain(const std::string &filename) const
{
    ofstream os(filename, ios::out | ios::trunc);
    if (!os.is_open())
    {
        cerr << "Failed to open file for writing" << endl;
        return;
    }

    Block *temp = _genesis_block;
    while (temp != nullptr)
    {
        temp->serialize(os);
        temp = temp->get_next_block();
    }

    os.close();
}

void Chain::load_chain(const std::string &filename)
{
    ifstream is(filename, ios::in);
    if (!is.is_open())
    {
        cerr << "Failed to open file for reading" << endl;
        return;
    }

    _genesis_block = nullptr;
    _current_block = nullptr;
    _length = 0;

    while (is)
    {
        // Check the stream state before deserializing
        streampos pos = is.tellg();
        Block *new_block = Block::deserialize(is, _current_block);

        // Check if deserialization was successful
        if (is && is.tellg() != pos)
        {
            if (_genesis_block == nullptr)
            {
                _genesis_block = new_block;
            }
            _current_block = new_block;
            _length++;
        }
        else
        {
            delete new_block;
        }
    }

    is.close();
}

Chain::~Chain()
{
    Block *current = _genesis_block;
    while (current != nullptr)
    {
        Block *next = current->get_next_block();
        delete current;
        current = next;
    }
}