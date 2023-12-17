#pragma once

#include<string>



#include <memory>
#include <unordered_map>
#include <vector>
#include <queue>
#include <fstream>
#include "bitstream.hpp"

namespace huffman {
    using std::shared_ptr;
    using std::unordered_map;
    using std::vector;
    using std::string;
    using std::ifstream;
    using std::ofstream;

    const string HUFFMAN_EXTENSION = ".huff";

    class huffman_tree {
        bool _is_leaf;
    public:
        char element;
        const shared_ptr<huffman_tree> left = nullptr;
        const shared_ptr<huffman_tree> right = nullptr;

        huffman_tree(char e) : element(e), _is_leaf(true) {}

        huffman_tree(const shared_ptr<huffman_tree> &l, const shared_ptr<huffman_tree> &r)
                : left(l), right(r), _is_leaf(false) {}

        bool is_leaf() const { return _is_leaf; }
    };


    shared_ptr<huffman_tree> build_huffman_tree(const unordered_map<char, int> &frequency_table);

    unordered_map<char, vector<bool>> build_encoding_map(const shared_ptr<huffman_tree> &tree);

    void compress(const std::string &file_name);

    void decompress(const std::string &file_name);
}
