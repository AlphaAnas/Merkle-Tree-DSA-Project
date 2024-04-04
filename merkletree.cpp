#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

//how to complie, cd "folder name where youll save file, for me it was 'Desktop'. " 
//  g++ -std=c++17 merkletree.cpp -o merkletree
//  ./merkletree

template <typename T>
int hashFunction(const T& data) 
{
    if constexpr (std::is_same_v<T, int>)       //hash function for integers
    {
        return data * 2; 
    } 

    else if constexpr (std::is_same_v<T, float>)    //hash function for floats
    {
        return int(data) * 2; 
    } 

    else if constexpr (std::is_same_v<T, std::string>)    // hash function for strings
    {
        int hash = 0;
        for (char c : data) 
        {
            hash += static_cast<int>(c);
        }
        return hash; 
    } 

    else {std::cout<<"unsupported data type"<<std::endl;}
}

template <typename T>

struct Node 
{
    int hash;
    Node* left;
    Node* right;

    Node(const T& data) 
    {
        hash = hashFunction(data);
        left = nullptr;
        right = nullptr;
    }

    Node(Node* l, Node* r) 
    {
        hash = l->hash + r->hash; // Combine hashes by summing.
        left = l;
        right = r;
    }
};
template <typename T>

class MerkleTree 
{
private:
    Node<T>* root;
    int originalRootHash;

    Node<T>* buildTree(std::vector<T>& data, int start, int end)
    {
        if (start == end)
        {
            return new Node<T>(data[start]);
        }

        int mid = (start + end) / 2;
        Node<T>* left = buildTree(data, start, mid);
        Node<T>* right = buildTree(data, mid + 1, end);

        return new Node<T>(left, right);
    }

    Node<T>* searchNode(Node<T>* node, const T& value) 
    {
        if (node == nullptr || node->hash == hashFunction(value)) 
        {
            return node;
        }

        Node<T>* leftResult = searchNode(node->left, value);
        if (leftResult != nullptr) 
        {
            return leftResult;
        }

        return searchNode(node->right, value);
    }

    void deleteSubtree(Node<T>* node) 
    {
        if (node == nullptr) 
        {
            return; // do nothing as nothing to delete.
        } 
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }

    void updateHash(Node<T>* node) 
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

    Node<T>* findNodeParent(Node<T>* parent, Node<T>* nodeToDelete) 
    {
        if (parent == nullptr) 
        {
            return nullptr;
        }

        if (parent->left == nodeToDelete || parent->right == nodeToDelete)
         {
            return parent;
        }

        Node<T>* leftResult = findNodeParent(parent->left, nodeToDelete);
        if (leftResult != nullptr) 
        {
            return leftResult;
        }

        return findNodeParent(parent->right, nodeToDelete);
    }

    void rehashParentNodes(Node<T>* startNode) 
    {
        Node<T>* current = startNode;
        while (current != nullptr) 
        {
            updateHash(current);
            current = findNodeParent(root, current);
        }
    }

public:
    MerkleTree(std::vector<T>& data) 
    {
        root = buildTree(data, 0, data.size() - 1);
        originalRootHash = root->hash;
    }

    ~MerkleTree() 
    {
        deleteSubtree(root);
    }

    void deleteValue(const T& value) 
    {
        Node<T>* nodeToDelete = searchNode(root, value);
        if (nodeToDelete == nullptr) 
        {
            std::cout << "The value that you are trying to delete is not in the tree!" << std::endl;
            return;
        }

        Node<T>* parent = findNodeParent(root, nodeToDelete);

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
            deleteSubtree(root);
            root = nullptr;
        }

        rehashParentNodes(parent);
    }

    bool verifyDataIntegrity() 
    {
        return root->hash == originalRootHash;
    }

    int getRootHash() 
    {
        return root->hash;
    }
};

int main() {

    //int merkle tree

    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};
    MerkleTree<int> intTree(data);

    std::cout << "Root hash before deletion: " << intTree.getRootHash() << std::endl;

    //int valueToDelete = 8; // case where val not in tree. gives error messege and integrity remians protected.
    int valueToDelete = 7; //deletes value but integrity compromised!
    intTree.deleteValue(valueToDelete);

    std::cout << "Root hash after deletion of " << valueToDelete << ": " << intTree.getRootHash() << std::endl;
    std::cout << "Data integrity verified after deletion: " << (intTree.verifyDataIntegrity() ? "Yes" : "No") << std::endl;


    //string merkle tree 

    std::vector<std::string> strData = {"hello", "world", "merkle", "tree"};
    MerkleTree<std::string> strTree(strData);

    std::cout << "Root hash of string tree: " << strTree.getRootHash() << std::endl;

    //std::string val = "hell"; // case where val not in tree. gives error messege and integrity remians protected.
    std::string val = "hello"; //deletes value but integrity compromised!
    strTree.deleteValue(val);

    std::cout << "Root hash after deletion of " << valueToDelete << ": " << strTree.getRootHash() << std::endl;
    std::cout << "Data integrity verified after deletion: " << (strTree.verifyDataIntegrity() ? "Yes" : "No") << std::endl;


    return 0;
}
