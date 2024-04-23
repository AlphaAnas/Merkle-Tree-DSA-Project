
#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include "merkle.cpp"

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ostringstream;
using std::string;
// int main()
string readFileIntoString(const string &path)
{
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '" << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str(); // returns the whole line as a string like 1,1.1\n2,2.2\n3,3.3\n
}
void printitems(vector<int> &items)
{
    for (auto &item : items)
    {
        cout << item << " ";
    }
    cout << endl;
}
int main_merkle()
{
    string filename("sample_data.txt");
    // string filename("Crypto.csv");
    string file_contents;
    std::map<int, std::vector<string>> csv_contents; // a dictionary to store each line of the csv file
                                                     // as a vector of strings
    char delimiter = ',';

    file_contents = readFileIntoString(filename);

    istringstream sstream(file_contents);
    std::vector<int> items;
    string record;

    int counter = 0;
    bool firstLine = true;
    while (std::getline(sstream, record))
    {
        if (firstLine)
        {
            firstLine = false;
            continue;
        }
        istringstream line(record);
        while (std::getline(line, record, delimiter))
        {
            // remove any leading or trailing white spaces
            record.erase(std::remove_if(record.begin(), record.end(), [](unsigned char x)
                                        { return std::isspace(x); }),
                         record.end());
            items.push_back(stoi(record));
        }
        // add the contents in the dictionary
        // csv_contents[counter] = items;
        // items.clear();
        // counter += 1;
    }
    printitems(items);
    MerkleTree<int> intTree(items); // vector to be used in making int merkle tree

    // will make it work after fixing the file input
    // std::ifstream file2("Football_managers.csv"); // reading data for str merkle tree
    // if (!file2.is_open())
    // {
    //     std::cerr << "Error ! unable to open the file. \n";
    //     return 1;
    // }

    // while (std::getline(file2, line2))
    // {
    //     if (firstLine2)
    //     {
    //         firstLine2 = false;
    //         continue;
    //     }
    //     std::stringstream ss(line2);
    //     std::string token2;
    //     while (std::getline(ss, token2, ','))
    //     {
    //         strData.push_back(token2);
    //     }
    // }
    // MerkleTree<std::string> strTree(strData); // vector to be used in making str merkle tree

    // // int tree

    // std::cout << std::endl;
    // std::cout << "Root hash before deletion int tree: " << intTree.getRootHash() << std::endl;
    // // int valueToDelete = 88898889;         // case where val not in tree. gives error messege and integrity remians protected.
    // int valueToDelete = 14; // deletes value but integrity compromised!
    // intTree.deleteValue(valueToDelete);
    // std::cout << "Root hash after deletion of " << valueToDelete << ": " << intTree.getRootHash() << std::endl;
    // std::cout << "Data integrity verified after deletion: " << (intTree.verifyDataIntegrity() ? "Yes" : "No") << std::endl;

    // // str tree

    // std::cout << std::endl;
    // std::cout << "Root hash before deletion string tree: " << strTree.getRootHash() << std::endl;
    // // std::string val = "bob";             // case where val not in tree. gives error messege and integrity remians protected.
    // std::string val = " Wolves "; // deletes value but integrity compromised! //7
    // strTree.deleteValue(val);
    // std::cout << "Root hash after deletion of " << val << ": " << strTree.getRootHash() << std::endl;
    // std::cout << "Data integrity verified after deletion: " << (strTree.verifyDataIntegrity() ? "Yes" : "No") << std::endl
    //           << std::endl;

    // std::cout << std::endl;
    // std::cout << "Root hash before deletion string tree: " << strTree.getRootHash() << std::endl;
    // // std::string val = "bob";             // case where val not in tree. gives error messege and integrity remians protected.
    // std::string val = " Wolves "; // deletes value but integrity compromised! //7
    // strTree.deleteValue(val);
    // std::cout << "Root hash after deletion of " << val << ": " << strTree.getRootHash() << std::endl;
    // std::cout << "Data integrity verified after deletion: " << (strTree.verifyDataIntegrity() ? "Yes" : "No") << std::endl
    //           << std::endl;

    return 0;
}
#endif
