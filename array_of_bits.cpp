//
// Created by Ahmed Ezzat on 09/12/2023.
//

#include "array_of_bits.hpp"

#include <iostream>
#include <string>

using std::string;
using std::ostream;


array_of_bits::array_of_bits() : _size(0), _data(1, 0) {}

int array_of_bits::capacity() const {
    return _data.size() << 3;
}

int array_of_bits::size() const {
    return _size;
}


array_of_bits& array_of_bits::push_back(bool bit) {
    if (_size >= capacity()) {
        _data.resize(_data.size() << 1);
    }
    _data[_size / 8] |= (bit << (_size % 8));
    _size++;
    return *this;
}

void array_of_bits::clear_bit(int index) {
    _data[index / 8] &= ~(1 << (index % 8));
}

void array_of_bits::pop_back() {
    assert(_size > 0);
    clear_bit(--_size);
}

void array_of_bits::clear() {
    while (_size > 0) pop_back();
}

string array_of_bits::to_string() const {
    string res;
    for (int i = 0; i < _size; i++) res += (*this)[i] ? '1' : '0';
    return res;
}

bool array_of_bits::operator[](int i) const {
    return (_data[i / 8] >> (i % 8)) & 1;
}

bool array_of_bits::operator<(const array_of_bits& other) const {
    if (_size != other._size) return _size < other._size;
    for (int i = 0; i < _size; i++) {
        if ((*this)[i] != other[i]) return (*this)[i] < other[i];
    }
    return false;
}

array_of_bits& array_of_bits::operator+=(const array_of_bits& other) {
    for (int i = 0; i < other._size; i++) push_back(other[i]);
    return *this;
}

ostream& operator<<(ostream& os, const array_of_bits& arr) {
    return os << arr._data;
}
