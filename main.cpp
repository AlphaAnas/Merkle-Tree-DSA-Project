
#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "merkle.cpp"

int main()
{

    // main_sdl(); // calling sdl function
    std::ifstream file("Crypto.csv"); // reading data for int merkle tree
    if (!file.is_open())
    {
        std::cerr << "Error ! unable to open the file. \n";
        return 1;
    }

    std::string line;
    std::vector<int> data;
    int value;
    bool firstLine = true;

    while (std::getline(file, line))
    {
        if (firstLine)
        {
            firstLine = false;
            continue;
        }
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ','))
        {
            value = std::stof(token);
            data.push_back(value);
        }
    }
    MerkleTree<int> intTree(data); // vector to be used in making int merkle tree

    std::ifstream file2("Football_managers.csv"); // reading data for str merkle tree
    if (!file2.is_open())
    {
        std::cerr << "Error ! unable to open the file. \n";
        return 1;
    }

    std::string line2;
    std::vector<std::string> strData;
    bool firstLine2 = true;

    while (std::getline(file2, line2))
    {
        if (firstLine2)
        {
            firstLine2 = false;
            continue;
        }
        std::stringstream ss(line2);
        std::string token2;
        while (std::getline(ss, token2, ','))
        {
            strData.push_back(token2);
        }
    }
    MerkleTree<std::string> strTree(strData); // vector to be used in making str merkle tree

    // int tree

    std::cout << std::endl;
    std::cout << "Root hash before deletion int tree: " << intTree.getRootHash() << std::endl;
    // int valueToDelete = 88898889;         // case where val not in tree. gives error messege and integrity remians protected.
    int valueToDelete = 14; // deletes value but integrity compromised!
    intTree.deleteValue(valueToDelete);
    std::cout << "Root hash after deletion of " << valueToDelete << ": " << intTree.getRootHash() << std::endl;
    std::cout << "Data integrity verified after deletion: " << (intTree.verifyDataIntegrity() ? "Yes" : "No") << std::endl;

    // str tree

    std::cout << std::endl;
    std::cout << "Root hash before deletion string tree: " << strTree.getRootHash() << std::endl;
    // std::string val = "bob";             // case where val not in tree. gives error messege and integrity remians protected.
    std::string val = " Wolves "; // deletes value but integrity compromised! //7
    strTree.deleteValue(val);
    std::cout << "Root hash after deletion of " << val << ": " << strTree.getRootHash() << std::endl;
    std::cout << "Data integrity verified after deletion: " << (strTree.verifyDataIntegrity() ? "Yes" : "No") << std::endl
              << std::endl;

    return 0;
};

#endif
