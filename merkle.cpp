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

template<typename T>
std::string Node<T>::sha256(int num){
    int static count=0;
    count++;
    //std::cout << count << std::endl;
    std::string result;
    //we convert the data to 256 bit binary so it can later be converted to 64 bit hex
    result = intToBinaryString(num);   

    //this function converts the data into a string of 64 bit hex
    result = binaryToHex(result);

    //these are default hard coded values. they are the first 32 bits of the square root of the first 8 prime numbers
    //for eg the first prime number is 2 and sqrt(2) = 1.41421356237
    //we take the fractional part of the number i.e. .41421356237
    //convert the fractional part into binary 
    //convert this binary to hex
    std::vector<std::string> h = {
    "6a09e667", "bb67ae85", "3c6ef372", "a54ff53a", 
    "510e527f", "9b05688c", "1f83d9ab", "5be0cd19"
    };

    //call the repeatedHash function
    result = repeatedHash(h,result);
    //std::cout<< "sha256 caleld";
    //std::cout << (result)<<" "<<num << std::endl;
    return result;
}

template<typename T>
std::string Node<T>::repeatedHash(std::vector<std::string>& values, std::string& data){

    std::string final_hash="  ";
    long long initial = hexToDecimal(data);
    //std::cout << initial << std::endl;
    std::vector<std::string> new_values;
    long long first = hexToDecimal(values[0]);
    long long first_answer = first * initial;
    //std::cout <<"first answer is "<< first_answer<<std::endl;
    new_values.push_back(decimalToHex(first_answer));
    for (int i=1;i<8;i++){
        //std::cout<< "going in loop"<<std::endl;
        long long answer;
        long long temp1 = hexToDecimal(values[i]);
        long long temp2 = hexToDecimal(new_values[i-1]);
        //std::cout << temp2 << " <- temp2 and temp1 -> " << temp1 << std::endl;
        // if (temp2==0){
        //     temp2= 1;
        // }
        answer = (temp1*temp2);
        //std::cout << i << "is " << answer << std::endl;
        new_values.push_back(decimalToHex(answer));
    } 
    for (int i = 0; i < 8; i++) {
    // If the size of new_values[i] is less than 8, pad zeros to the left
        if (new_values[i].size() < 8) {
            new_values[i] = std::string(8 - new_values[i].size(), '0') + new_values[i];
        }
        final_hash += new_values[i];
    }
    //std::cout<<final_hash<< std::endl;
    return final_hash;
}

template<typename T>
std::string Node<T>::intToBinaryString(int num) {
    return std::bitset<sizeof(num) * 64>(num).to_string();
}

template<typename T>
std::string Node<T>::decimalToHex(int decimal) {
    //std::cout << "decimal to hex called" <<std::endl;
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << decimal;
    std::string hex = ss.str();
    return hex;
}

template<typename T>
long long Node<T>::hexToDecimal(const std::string& hex) {
    std::stringstream ss;
    ss << std::hex << hex;
    long long decimal;
    ss >> decimal;
    //std::cout << "decimal is " <<decimal<<std::endl;
    return decimal;
}

template<typename T>
std::string Node<T>::binaryToHex(const std::string& binary) {
    // Ensure the binary string length is a multiple of 4
    int padding = binary.size() % 4;

    std::stringstream hexStream;
    for (size_t i = 0; i < binary.size(); i += 4) {
        std::string nibble = binary.substr(i, 4);
        int decimal = std::bitset<4>(nibble).to_ulong();
        hexStream << std::hex << decimal;
    }

    return hexStream.str();
};

template <typename T>
long long Node<T>::hashFunction(const T &data)
{ 
    if constexpr (std::is_same_v<T, int>)                   // hash function for integers
    {
        //sha256 function is given the key for eg key = 10
        std::string result = (sha256(data));
        //std::cout<< result << std::endl;
        long long num = hexToDecimal(result.substr(0, 10));
        //std::cout << num << " " << data <<std::endl;
        return num;
    } 
    else if constexpr (std::is_same_v<T, float>)            // hash function for floats
    {
        int temp = static_cast<int>(data);
        std::string result = (sha256(temp));
        //std::cout<< result << std::endl;
        long long num = hexToDecimal(result.substr(0, 10));
        return num;
    }
    else if constexpr (std::is_same_v<T, std::string>)      // hash function for strings
    {
        int hash = 0;
        for (char c : data)
        {
            hash += static_cast<int>(c);
        } 
        std::string result = (sha256(hash));
        //std::cout<< result << std::endl;
        long long num = hexToDecimal(result.substr(0, 10));
        return num;
    } 
    else
    {
        std::cout << "unsupported data type" << std::endl;
        return 0;
    }
}

//constructor
template <typename T>
MerkleTree<T>::MerkleTree(std::vector<T> &data)
{
    root = buildTree(data, 0, data.size() - 1);
    originalRootHash = root->hash;
}

//destructor
template <typename T>
MerkleTree<T>::~MerkleTree()
{
    deleteSubtree(root);
}

//deletes a value
template <typename T>
void MerkleTree<T>::deleteValue(const T &value)
{
    //std::cout<<value<<std::endl;
    Node<T> *nodeToDelete = searchNode(root, value);
    //std::cout<< root<<" "<<value<<std::endl;
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
        deleteSubtree(root);    //deletes value
        root = nullptr;         //assigns it null
    }

    rehashParentNodes(parent);
}

//verifies integrity by comparinf cureent hash value to old hash value!
template <typename T>
bool MerkleTree<T>::verifyDataIntegrity()
{
    return root->hash == originalRootHash;
}

//getter
template <typename T>
long long MerkleTree<T>::getRootHash()
{
    return root->hash;
}


//makes merkle tree recursively
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

//node search recursively
template <typename T>
Node<T> *MerkleTree<T>::searchNode(Node<T> *node, const T &value)
{
    //std::cout<<value<<std::endl;
    //std::cout<<node<<std::endl;
    if ((node == nullptr) || node->hash == node->hashFunction(value))
    {
        //std::cout<<node<<std::endl;
        return node;
    }

    Node<T> *leftResult = searchNode(node->left, value);
    if (leftResult != nullptr)
    {
        return leftResult;
    }

    return searchNode(node->right, value);
}


//deletes subtree
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
