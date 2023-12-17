#pragma once

#include<fstream>
#include<vector>


class ibitstream {
    char data;
    int index;
    std::ifstream input;

    bool read();
    
public:
    ibitstream(const std::string &file_name) : data(0), index(-1), input(file_name) {
    }
    
    template<typename T>
    ibitstream &operator>>(T) = delete;
    ibitstream &operator>>(bool &bit);
    ibitstream &operator>>(char& ch);
    
    ~ibitstream() {
        input.close();
    }
};

class obitstream {
    char data;
    int index;
    std::ofstream out;
public:
    obitstream(const std::string &file_name) : data(0), index(7), out(file_name) {
    }

    template<typename T>
    ibitstream &operator<<(T) = delete;
    obitstream &operator<<(const bool& bit);
    obitstream &operator<<(const char & ch);
    obitstream &operator<<(const std::vector<bool> &code);

    ~obitstream() {
        if (index != 7) {
            out << data;
        }
        out.close();
    }
};

