#include "merkle.hpp"

// Constructor with data
template <typename T>
Node<T>::Node(const T &data)
{
    hash = hashFunction(data);
    left = nullptr;
    right = nullptr;
}

// Constructor for combining nodes
template <typename T>
Node<T>::Node(Node *l, Node *r)
{
    hash = l->hash + r->hash; // Combine hashes by summing.
    left = l;
    right = r;
}

template <typename T>
int Node<T>::hashFunction(const T &data)
{
    if constexpr (std::is_same_v<T, int>) // hash function for integers
    {
        return data;
    }
    else if constexpr (std::is_same_v<T, float>) // hash function for floats
    {
        return static_cast<int>(data);
    }
    else if constexpr (std::is_same_v<T, std::string>) // hash function for strings
    {
        int hash = 0;
        for (char c : data)
        {
            hash += static_cast<int>(c);
        }
        return hash;
    }
    else
    {
        std::cout << "unsupported data type" << std::endl;
        return 0;
    }
}

// constructor
template <typename T>
MerkleTree<T>::MerkleTree(std::vector<T> &data)
{
    root = buildTree(data, 0, data.size() - 1);
    originalRootHash = root->hash;
}

// destructor
template <typename T>
MerkleTree<T>::~MerkleTree()
{
    deleteSubtree(root);
}

// deletes a value
template <typename T>
void MerkleTree<T>::deleteValue(const T &value)
{
    Node<T> *nodeToDelete = searchNode(root, value);
    if (nodeToDelete == nullptr)
    {
        std::cout << "The value that you are trying to delete is not in the tree!" << std::endl;
        return;
    }

    Node<T> *parent = findNodeParent(root, nodeToDelete);

    if (parent != nullptr)
    {
        if (parent->left == nodeToDelete)
        {
            parent->left = nullptr;
        }
        else
        {
            parent->right = nullptr;
        }
    }
    else
    {
        deleteSubtree(root); // deletes value
        root = nullptr;      // assigns it null
    }

    rehashParentNodes(parent);
}

// verifies integrity by comparinf cureent hash value to old hash value!
template <typename T>
bool MerkleTree<T>::verifyDataIntegrity()
{
    return root->hash == originalRootHash;
}

// getter
template <typename T>
int MerkleTree<T>::getRootHash()
{
    return root->hash;
}

// makes merkle tree recursively
template <typename T>
Node<T> *MerkleTree<T>::buildTree(std::vector<T> &data, int start, int end)
{
    if (start == end)
    {
        return new Node<T>(data[start]);
    }

    int mid = (start + end) / 2;
    Node<T> *left = buildTree(data, start, mid);
    Node<T> *right = buildTree(data, mid + 1, end);

    return new Node<T>(left, right);
}

// node search recursively
template <typename T>
Node<T> *MerkleTree<T>::searchNode(Node<T> *node, const T &value)
{
    if (node == nullptr || node->hash == node->hashFunction(value))
    {
        return node;
    }

    Node<T> *leftResult = searchNode(node->left, value);
    if (leftResult != nullptr)
    {
        return leftResult;
    }

    return searchNode(node->right, value);
}

// deletes subtree
template <typename T>
void MerkleTree<T>::deleteSubtree(Node<T> *node)
{
    if (node == nullptr)
    {
        return; // do nothing as nothing to delete.
    }
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

// Updates the hash value of a node
template <typename T>
void MerkleTree<T>::updateHash(Node<T> *node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->left != nullptr && node->right != nullptr)
    {
        node->hash = node->left->hash + node->right->hash;
    }
    else if (node->left != nullptr)
    {
        node->hash = node->left->hash;
    }
    else if (node->right != nullptr)
    {
        node->hash = node->right->hash;
    }
}

// Finds the parent of a node
template <typename T>
Node<T> *MerkleTree<T>::findNodeParent(Node<T> *parent, Node<T> *nodeToDelete)
{
    if (parent == nullptr)
    {
        return nullptr;
    }

    if (parent->left == nodeToDelete || parent->right == nodeToDelete)
    {
        return parent;
    }

    Node<T> *leftResult = findNodeParent(parent->left, nodeToDelete);
    if (leftResult != nullptr)
    {
        return leftResult;
    }

    return findNodeParent(parent->right, nodeToDelete);
}

// Rehashes parent nodes
template <typename T>
void MerkleTree<T>::rehashParentNodes(Node<T> *startNode)
{
    Node<T> *current = startNode;
    while (current != nullptr)
    {
        updateHash(current);
        current = findNodeParent(root, current);
    }
}

// Explicit template instantiation - the types we'll be using.
template class Node<int>;
template class Node<float>;
template class Node<std::string>;
template class MerkleTree<int>;
template class MerkleTree<float>;
template class MerkleTree<std::string>;