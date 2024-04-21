#ifndef MERKLE_HPP
#define MERKLE_HPP

#include <iostream>
#include <vector>
#include <string>
using namespace std;
template <typename T> // Forward declaration of MerkleTree class
class MerkleTree;

template <typename T>
struct Node // Node structure for MerkleTree
{
    int hash;    // Hash value of the node
    Node *left;  // Pointer to the left child node
    Node *right; // Pointer to the right child node

    Node(const T &data);    // Constructor with data
    Node(Node *l, Node *r); // Constructor for combining nodes

private:
    int hashFunction(const T &data); // Private hash function for generating hash value
    friend class MerkleTree<T>;      // Allowing MerkleTree class to access private members
};

template <typename T>
class MerkleTree // MerkleTree class
{
private:
    Node<T> *root;        // Pointer to the root node
    int originalRootHash; // Hash value of the original root node

    // Private member functions
    Node<T> *buildTree(std::vector<T> &data, int start, int end);    // Builds the Merkle tree
    Node<T> *searchNode(Node<T> *node, const T &value);              // Searches for a node
    void deleteSubtree(Node<T> *node);                               // Deletes a subtree
    void updateHash(Node<T> *node);                                  // Updates the hash value of a node
    Node<T> *findNodeParent(Node<T> *parent, Node<T> *nodeToDelete); // Finds the parent of a node
    void rehashParentNodes(Node<T> *startNode);                      // Rehashes parent nodes

public:
    // Public member functions
    MerkleTree(std::vector<T> &data); // Constructor
    ~MerkleTree();                    // Destructor
    void deleteValue(const T &value); // Deletes a value
    bool verifyDataIntegrity();       // Verifies the integrity of the tree
    int getRootHash();                // Returns the hash value of the root node
};
#endif /* MERKLE_HPP */