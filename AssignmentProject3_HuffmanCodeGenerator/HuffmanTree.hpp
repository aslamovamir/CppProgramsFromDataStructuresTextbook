#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <stack>
#include <map>
#include <vector>
#include <string>
#include <cstdlib>


#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"


class HuffmanTree: public HuffmanTreeBase {
    public:
        std::string compress(const std::string inputStr);
        std::string serializeTree() const;
        std::string decompress(const std::string inputCode, const std::string serializedTree);

    //helper methods
    public:
        void encodeMap(HuffmanNode *root, std::string str, std::map<char, std::string> &encMap);
        std::string helpSerialize(HuffmanNode *node) const;
        HuffmanNode *makeTree(const std::string s) const;
    //pribvate data memeber to store the root node of the heap
    private:
        HuffmanNode *rootNode;
};



#endif