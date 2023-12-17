#paragma once

#include <iostream>
#include <string>

using std::string;
using std::ostream;


class array_of_bits {
    string _data;
    int _size;
    void clear_bit(int index);
public:
    array_of_bits();
    int capacity() const;
    int size() const;
    array_of_bits& push_back(bool bit);
    void pop_back();
    void clear();
    string to_string() const;
    bool operator[](int index) const;
    bool operator<(const array_of_bits& other) const;
    array_of_bits& operator+=(const array_of_bits& other);
    friend ostream& operator<<(ostream& os, const array_of_bits& arr);
};


