#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <cstring>
#include <string>
#include <ctime>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <queue>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <utility>
#include <sstream>

#define ABS(a) ((a) < 0 ? -(a) : (a))
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)

std::vector<std::vector<std::string>> items;

void read_tsv(char *fname)
{
    std::ifstream ifs(fname);
    if (ifs.fail())
    {
        std::cerr << "error" << std::endl;
        return;
    }
    std::string line;
    while (getline(ifs, line))
    {
        std::stringstream ss(line);
        std::vector<std::string> item;
        std::string tmp;
        while (getline(ss, tmp, '\t'))
        {
            item.push_back(tmp);
        }
        items.push_back(item);
    }
    REP(i, items.size())
    {
        REP(j, items[i].size())
        std::cout << "[" << i << "][" << j << "]: " << items[i][j] << std::endl;
    }
    return;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " file" << std::endl;
        std::exit(-1);
    }
    read_tsv(argv[1]);
    return 0;
}