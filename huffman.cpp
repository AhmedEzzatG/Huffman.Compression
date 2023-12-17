
#include "huffman.hpp"

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


shared_ptr<huffman_tree> huffman::build_huffman_tree(const unordered_map<char, int> & frequency_table) {
    std::priority_queue<
            std::pair<int, shared_ptr<huffman_tree>>,
            vector<std::pair<int, shared_ptr<huffman_tree>>>,
            std::greater<>> pq;
    for (auto &i: frequency_table) {
        shared_ptr<huffman_tree> ptr(new huffman_tree(i.first));
        pq.emplace(0, ptr);
    }
    while (pq.size() > 1) {
        auto l = pq.top();
        pq.pop();
        auto r = pq.top();
        pq.pop();
        shared_ptr<huffman_tree> ptr(new huffman_tree(l.second, r.second));
        pq.emplace(l.first + r.first, ptr);
    }
    return pq.top().second;
}

void _build_encoding_map(const shared_ptr<huffman_tree>& node, vector<bool>& code, unordered_map<char, vector<bool>>& encoding) {
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

unordered_map<char, vector<bool>> huffman::build_encoding_map(const shared_ptr<huffman_tree>& tree) {
    vector<bool> code;
    unordered_map<char, vector<bool>> encoding;
    _build_encoding_map(tree, code, encoding);
    return encoding;
}

void serialize_tree(const shared_ptr<huffman_tree>& node, obitstream& bs) {
    if (node->is_leaf()) {
        bs << true << node->element;
        return;
    }
    bs << false;
    serialize_tree(node->left, bs);
    serialize_tree(node->right, bs);
}

shared_ptr<huffman_tree> deserialize_tree(ibitstream& bs) {
    bool is_leaf;
    bs >> is_leaf;
    if (is_leaf) {
        char ch;
        bs >> ch;
        return std::make_shared<huffman_tree>(ch);
    }
    shared_ptr<huffman_tree> l = deserialize_tree(bs);
    shared_ptr<huffman_tree> r = deserialize_tree(bs);
    return std::make_shared<huffman_tree>(l, r);
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
        shared_ptr<huffman_tree> node = tree;
        bool bit;
        while (!node->is_leaf()) {
            bs >> bit;
            node = (bit ? node->right : node->left);
        }
        if (node->element == EOF) {
            return;
        }
        file << node->element;
    }
}
