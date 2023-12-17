
#include "huffman.hpp"

#include <memory>

using namespace huffman;


unordered_map<char, int> generate_frequency_table(const string& file_name) {
    ifstream file(file_name);
    char ch;
    unordered_map<char, int> mp;
    while (file.get(ch)) mp[ch]++;
    mp[EOF] = 1;
    file.close();
    return mp;
}


unique_ptr<huffman_tree> huffman::build_huffman_tree(const unordered_map<char, int> & frequency_table) {
    using node_type = std::pair<int, unique_ptr<huffman_tree>>;
    my_priority_queue<node_type, vector<node_type>, std::greater<>> pq;
    for (auto &i: frequency_table) {
        pq.emplace(i.second, new huffman_tree(i.first));
    }
    while (pq.size() > 1) {
        node_type l, r;
        pq.pop(l);
        pq.pop(r);
        unique_ptr<huffman_tree> ptr = std::make_unique<huffman_tree>(std::move(l.second), std::move(r.second));
        pq.emplace(l.first + r.first, ptr.release());
    }
    node_type root;
    pq.pop(root);
    return std::move(root.second);
}

void _build_encoding_map(const unique_ptr<huffman_tree>& node, vector<bool>& code, unordered_map<char, vector<bool>>& encoding) {
    if (node->is_leaf()) {
        encoding[node->element] = code;
        return;
    }
    code.push_back(false);
    _build_encoding_map(node->left, code, encoding);
    code.back() = true;
    _build_encoding_map(node->right, code, encoding);
    code.pop_back();
}

unordered_map<char, vector<bool>> huffman::build_encoding_map(const unique_ptr<huffman_tree>& tree) {
    vector<bool> code;
    unordered_map<char, vector<bool>> encoding;
    _build_encoding_map(tree, code, encoding);
    return encoding;
}

void serialize_tree(const unique_ptr<huffman_tree>& node, obitstream& bs) {
    if (node->is_leaf()) {
        bs << true << node->element;
        return;
    }
    bs << false;
    serialize_tree(node->left, bs);
    serialize_tree(node->right, bs);
}

unique_ptr<huffman_tree> deserialize_tree(ibitstream& bs) {
    bool is_leaf;
    bs >> is_leaf;
    if (is_leaf) {
        char ch;
        bs >> ch;
        return std::make_unique<huffman_tree>(ch);
    }
    unique_ptr<huffman_tree> l = deserialize_tree(bs);
    unique_ptr<huffman_tree> r = deserialize_tree(bs);
    return std::make_unique<huffman_tree>(std::move(l), std::move(r));
}


void huffman::compress(const string &file_name) {
    auto frequency = generate_frequency_table(file_name);
    auto tree = build_huffman_tree(frequency);
    auto encoding = build_encoding_map(tree);
    obitstream bs(file_name + HUFFMAN_EXTENSION);
    
    
    serialize_tree(tree, bs);
    ifstream file(file_name);
    char ch;
    while (file.get(ch)) {
        bs << encoding[ch];
    }
    bs << encoding[EOF];
    file.close();
}

void huffman::decompress(const string &file_name) {
    ibitstream bs(file_name);
    auto tree = deserialize_tree(bs);
    ofstream file(file_name + ".txt");
    while (true) {
        huffman_tree const * node = tree.get();
        bool bit;
        while (!node->is_leaf()) {
            bs >> bit;
            node = (bit ? node->right : node->left).get();
        }
        if (node->element == EOF) {
            return;
        }
        file << node->element;
    }
}
