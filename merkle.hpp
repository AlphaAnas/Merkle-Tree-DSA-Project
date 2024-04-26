#include <iostream>
#include <vector>
#include <string>
//#include <bits/stdc++.h>
#include <bitset>
#include <sstream>
#include <cstring>
#include <iomanip>


template <typename T>   // Forward declaration of MerkleTree class
class MerkleTree;

template <typename T>
struct Node             // Node structure for MerkleTree
{
    long long hash;       // Hash value of the node
    Node *left;     // Pointer to the left child node
    Node *right;    // Pointer to the right child node

    Node(const T &data);    // Constructor with data
    Node(Node *l, Node *r); // Constructor for combining nodes

private:
    
    long long hashFunction(const T &data);    // Private hash function for generating hash value
    std::string intToBinaryString(int num);
    std::string binaryToHex(const std::string& binary);
    std::string repeatedHash(std::vector<std::string>& values, std::string& data);
    long long hexToDecimal(const std::string &data);
    std::string decimalToHex(int decimal);
    std::string sha256(int num);
    friend class MerkleTree<T>;         // Allowing MerkleTree class to access private members
};


template <typename T>
class MerkleTree            // MerkleTree class
{
private:
    Node<T> *root;          // Pointer to the root node
    long long originalRootHash;   // Hash value of the original root node

    // Private member functions
    Node<T> *buildTree(std::vector<T> &data, int start, int end);      // Builds the Merkle tree
    Node<T> *searchNode(Node<T> *node, const T &value);                // Searches for a node
    void deleteSubtree(Node<T> *node);                                 // Deletes a subtree
    void updateHash(Node<T> *node);                                    // Updates the hash value of a node
    Node<T> *findNodeParent(Node<T> *parent, Node<T> *nodeToDelete);    // Finds the parent of a node
    void rehashParentNodes(Node<T> *startNode);                         // Rehashes parent nodes

public:
    // Public member functions
    MerkleTree(std::vector<T> &data);       // Constructor
    ~MerkleTree();                          // Destructor
    void deleteValue(const T &value);       // Deletes a value
    bool verifyDataIntegrity();             // Verifies the integrity of the tree
    long long getRootHash();                      // Returns the hash value of the root node
};
