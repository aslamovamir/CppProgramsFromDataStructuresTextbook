#ifndef HUFFMANBASE_H
#define HUFFMANBASE_H

#include <cstddef>
#include <string>
#include <iostream>

class HuffmanNode {
public:
  HuffmanNode(char c, size_t f, HuffmanNode *p, HuffmanNode *l, HuffmanNode *r) : character(c), frequency(f), parent(p), left(l), right(r) {};
  HuffmanNode(char c, size_t f) : HuffmanNode(c, f, nullptr, nullptr, nullptr) {};

  char getCharacter() const;
  size_t getFrequency() const;

  bool isLeaf() const;
  bool isBranch() const;
  bool isRoot() const;

  class Compare {
  public:
    Compare(bool lessThan = true) : lessThan(lessThan) {};
    bool operator()(const HuffmanNode &n1, const HuffmanNode &n2) const;
    bool operator()(const HuffmanNode *n1, const HuffmanNode *n2) const;
  private:
    bool lessThan;
  };

private:
  char character;
  size_t frequency;

public: 
  HuffmanNode *parent;
  HuffmanNode *left;
  HuffmanNode *right;
};

class HuffmanTreeBase {
  public:
  virtual std::string compress(const std::string inputStr) = 0;
  virtual std::string serializeTree() const = 0;
  virtual std::string decompress(const std::string inputCode, const std::string serializedTree) = 0;
};

#endif /* HUFFMANBASE_H */