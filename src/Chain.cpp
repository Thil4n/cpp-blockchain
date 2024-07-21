#include "Chain.h"
#include <iostream>

using namespace std;

Chain::Chain()
{
    _difficulty = 0;
    _length = 0;
    cout << _length;
    _current_block = new Block(nullptr, "Genesis Block", _difficulty);
    _genesis_block = _current_block;
    _length++;
}

void Chain::set_difficulty(int difficulty)
{
    _difficulty = difficulty;
}

void Chain::append_data(string data)
{
    Block *new_block = new Block(_current_block, data, _difficulty);
    _current_block = new_block;
    _length++;
}

void Chain::print_chain() const
{
    Block *temp = _genesis_block;

    for (int i = 0; i < _length; i++)
    {

        // cout << "block : " << i << endl;
        // temp = temp->get_next_block();
    }
}

Chain::~Chain()
{
    Block *current = _current_block;
    while (current != nullptr)
    {
        Block *prev = current->get_next_block();
        delete current;
        current = prev;
    }
}
