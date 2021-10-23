#include "HuffmanTree.hpp"


std::string HuffmanTree::compress(const std::string inputStr) {

    //a map will be used to store characters as the keys and the thier
    //associated frequencies as the values
    //stl iterators are used to give accurate results in case the size of the 
    //input string is too large
    std::map <char, size_t> freq_char_map;
    std::map <char, size_t>::const_iterator itarat;

    //frequencies for each character are counted, and mapped toegther with their keys
    for (std::string::const_iterator iter = inputStr.begin(); iter != inputStr.end(); iter++) {
        freq_char_map[*iter] += 1;
    }

    //The characters and their frequencies are inserted into a priority queue(sorted first by the lowest frequency and then lexicographically
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> queue;
    for (itarat = freq_char_map.begin(); itarat != freq_char_map.end(); itarat++) {
        HuffmanNode* new_pair_node;
        new_pair_node = new HuffmanNode(itarat->first, itarat->second);
        queue.insert(new_pair_node);
    }
    

    //the tree is constructed into the heap until only 1 node remains in the heap
    while(queue.size() != 1) {
        
        //first smallest frequency node
        HuffmanNode *firstNode;
        firstNode = queue.min();
        queue.removeMin();
        //second smallest frequency node
        HuffmanNode *secondNode;
        secondNode = queue.min();
        queue.removeMin();

        //new frequency value of the parent node; frequency values of the children are added
        size_t new_freq = firstNode->getFrequency() + secondNode->getFrequency();
        HuffmanNode *newParent = new HuffmanNode('\0', new_freq, nullptr, firstNode, secondNode);

        //the new node is inserted back into the heap
        queue.insert(newParent);
    }

    //this map will serve the purpose of storing the characters 
    //now with their associated binary code representations
    std::map<char, std::string> encMap;
    
    //the new root node of the heap
    HuffmanNode *heap = queue.min();

    std::string binaryCode = "";
    encodeMap(heap, binaryCode, encMap);

    std::string compressedStr = "";
    //again, stl iterators are used to ensure accuracy in the face of large input size
    for (std::string::const_iterator iter = inputStr.begin(); iter != inputStr.end(); iter++) {
        compressedStr = compressedStr + encMap[*iter];
    }  

    //private data memeber of Huffman pointer node 
    //is given a value of the root of the heap 
    rootNode = heap;
    
    return compressedStr;
} 


//helper function for the compress function it takes in the reference to the map, 
//a temporary iterator string, and the root node of the heap, 
//recursively calls itself, and if at the leaf, so-far-appended string is made the value
//of the char key that is at that leaf, and this pair is stored into the map
void HuffmanTree::encodeMap(HuffmanNode *root, std::string str, std::map<char, std::string> &huffmanCodeMap) {

    //if the node is outside the tree, the function terminates
    if (root == nullptr) {
        return;
    }
    //if at the leaf, the character is stores into the map
    if (root->isLeaf()) {
        huffmanCodeMap[root->getCharacter()] = str;
    }

    //recursive calls of the function
    //if the function recurs to the left child, 0 is appended to the string
    //1 is appended if the node recurs to the right child
    encodeMap(root->left, str + "0", huffmanCodeMap);
    encodeMap(root->right, str + "1", huffmanCodeMap);
}


//a helper function that takes in the root node of the heap and returns the
//serialized tree representation in string form
std::string HuffmanTree::helpSerialize(HuffmanNode *node) const {
    std::string result = "";

    //if the node is at a branch, the function recurses, appending B
    //to the string to indicate the presence of the branch at this point
    if (node->isBranch()) {
        result = result + helpSerialize(node->left) + helpSerialize(node->right) + "B";
        return result;
    } else { //else if at a leaf, the character from this leaf is appended to the string
        result = result + "L" + node->getCharacter();
        return result;
    }
}


//main serialize function that calls itse helper function
//the helper function is given the root node of the heap,
//assuming that the heap is constructed alread; the helper 
//function takes in the private data memeber Huffman node pointer
std::string HuffmanTree::serializeTree() const {

    std::string output = helpSerialize(rootNode);
    return output;
}


//helper function for the decompress function
//it takes in the serialized string representation of the heap,
//constructs the heap, and then returns the root nopde pointer of the heap
HuffmanNode *HuffmanTree::makeTree(const std::string s) const {
    size_t parentFreq;
    //an stl stack is used to manage the chars and the associated branch indicators
    std::stack<HuffmanNode*> treeStack;

    //if the leaf indicator is met, we push the char stored next to it to the stack
    //if branch indicator is met, last two chars are pulled up, made children of 
    //a new parent node, which is then pushed back to the stack
    for (std::string::const_iterator iter = s.begin(); iter != s.end(); iter++) {
        if (*iter == 'L') {
            iter++;
            HuffmanNode *nodeToInsert = new HuffmanNode(*iter, 0);
            treeStack.push(nodeToInsert);
        }
        else  {
            HuffmanNode *rightNode = treeStack.top();
            treeStack.pop();
            HuffmanNode *leftNode = treeStack.top();
            treeStack.pop();
            parentFreq = leftNode->getFrequency() + rightNode->getFrequency();
            HuffmanNode *parentNode = new HuffmanNode('\0', parentFreq, nullptr, leftNode, rightNode);
            
            treeStack.push(parentNode);
        }
    }
    return treeStack.top();
}


//this functions relies on its helper function, makeTree, to rebuild the tree with the help of the serialized tree representation
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
    
    std::string decodedStr = "";
    HuffmanNode *rootTree = makeTree(serializedTree);

    //stl iterators used to ensure accuracy
    HuffmanNode *iterat = rootNode;
    //if 0 is met in the binary code, the iterator goes down to the left child
    //if 1 is met, the iterator goes down to the right child
    //at each move, the iterator is checked if it is at a leaf, if so, the char from the leaf is appended
    //to the decoded string
    for (std::string::const_iterator iter = inputCode.begin(); iter != inputCode.end(); iter++) {
    
        if (*iter == '0') {
            iterat = iterat->left;
            if (iterat->isLeaf()) {
                decodedStr += iterat->getCharacter();
                iterat = rootTree;
            }
        } else {
            iterat = iterat->right;
            if (iterat->isLeaf()) {
                decodedStr += iterat->getCharacter();
                iterat = rootTree;
            } 
        }
    }
    return decodedStr;
}
