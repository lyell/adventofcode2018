#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <limits>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "missing input file in arguments!" << std::endl;
        return 1;
    }

    typedef std::vector<std::string> Lines;
    Lines lines;

    std::ifstream inputFile(argv[1]);
    std::string line;
    while (!inputFile.eof()) {
        std::getline(inputFile, line);
        lines.push_back(line);
        std::cout << "line: " << line << std::endl;
    }

    return 0;
}
