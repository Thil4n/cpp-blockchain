#include "Chain.h"
#include <iostream>

using namespace std;

Chain::Chain()
{
    _length = 0;
    cout << _length;
    _current_block = new Block(nullptr, nullptr, 0); // create genesis block
    _genesis_block = _current_block;
    _length++;
}

void Chain::append_data(const uint8_t *data, uint8_t size)
{
    Block *new_block = new Block(_current_block, data, size);
    _current_block = new_block;
    _length++;
}

void Chain::print_chain() const
{
    Block *temp = _genesis_block;

    for (int i = 0; i < _length; i++)
    {

        cout << "block : " << i << endl;
        cout << temp->get_hash_str() << endl;
        temp = temp->get_next_block();
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
