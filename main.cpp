#include "huffman.hpp"

int main(int argc, const char * argv[]) {
    if (argc != 3) {
        throw std::invalid_argument("Usage: huffman [c|d] [file_name]");
    }
    const char *file_name = argv[2];
    ibitstream bs(file_name);

    if (argv[1][0] == 'c') {
        huffman::compress(file_name);
    } else {
        huffman::decompress(file_name);
    }
    
}