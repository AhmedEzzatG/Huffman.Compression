
#include "bitstream.hpp"


bool ibitstream::read() {
    if (index == -1) {
        input.read(&data, 1);
        index = 7;
    }
    bool bit = (data >> index) & 1;
    index--;
    return bit;
}

ibitstream& ibitstream::operator>>(bool &bit) {
    bit = read();
    return *this;
}

ibitstream& ibitstream::operator>>(char& ch) {
    ch = 0;
    for (int i = 7; i >= 0; i--) {
        bool bit = read();
        ch |= (bit << i);
    }
    return *this;
}


obitstream& obitstream::operator<<(const bool& bit) {
    data |= (bit << index);
    index--;
    if (index == -1) {
        out << data;
        data = 0;
        index = 7;
    }
    return *this;
}

obitstream& obitstream::operator<<(const char & ch) {
    for (int i = 7; i >= 0; i--) {
        bool bit = (ch >> i) & 1;
        (*this) << bit;
    }
    return *this;
}

obitstream& obitstream::operator<<(const std::vector<bool> &code) {
    for (auto bit : code) {
        (*this) << (bool)bit;
    }
    return *this;
}

