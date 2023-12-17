#pragma once

#include<string>



#include <memory>
#include <unordered_map>
#include <vector>
#include <queue>
#include <fstream>
#include "bitstream.hpp"
#include "my_priority_queue.hpp"

namespace huffman {
    using std::unique_ptr;
    using std::unordered_map;
    using std::vector;
    using std::string;
    using std::ifstream;
    using std::ofstream;

    const string HUFFMAN_EXTENSION = ".huff";

    class huffman_tree {
    public:
        char element;
        mutable unique_ptr<huffman_tree> left = nullptr;
        mutable unique_ptr<huffman_tree> right = nullptr;

        huffman_tree(char e) : element(e) {}

        huffman_tree(unique_ptr<huffman_tree> l, unique_ptr<huffman_tree> r)
                : left(l.release()), right(r.release()) {}

        bool is_leaf() const { return (left == nullptr); }

        bool operator<(const huffman_tree &other) const {
            return element < other.element;
        }
        bool operator>(const huffman_tree &other) const {
            return element > other.element;
        }
    };


    unique_ptr<huffman_tree> build_huffman_tree(const unordered_map<char, int> &frequency_table);

    unordered_map<char, vector<bool>> build_encoding_map(const unique_ptr<huffman_tree> &tree);

    void compress(const std::string &file_name);

    void decompress(const std::string &file_name);
}
