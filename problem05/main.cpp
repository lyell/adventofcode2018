#include <boost/regex.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <stack>
#include <limits>

bool react(char c1, char c2) {
    return ((std::isupper(c1) && std::islower(c2)) ||
        (std::islower(c1) && std::isupper(c2))) &&
            std::tolower(c1) == std::tolower(c2);
}

size_t process(std::string const& line) {
    std::stack<char> s;
    for (size_t i = 0; i < line.length(); ++i) {
        if (!s.empty() && react(s.top(), line[i])) {
            // std::cout << "pop " << s.top() << " " << line[i] << std::endl;
            s.pop();
        } else {
            // std::cout << "push " << line[i] << std::endl;
            s.push(line[i]);
        }
    }

    return s.size();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "missing input file in arguments!" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    //std::string line("dabAcCaCBAcCcaDA");
    std::string line;
    while (!inputFile.eof()) {
        std::getline(inputFile, line);
    }

    size_t firstResult = process(line);

    std::cout << "part one: " << firstResult << std::endl;

    size_t minResult = std::numeric_limits<size_t>::max();
    for (char c = 'a'; c <= 'z'; ++c) {
        std::cout << "removing " << c << std::endl;
        std::string testLine;
        for (int i = 0; i < line.size(); ++i) {
            if (std::tolower(line[i]) != c) {
                testLine.push_back(line[i]);
            }
        }

        size_t result = process(testLine);
        if (result < minResult) {
            minResult = result;
        }
    }

    std::cout << "part two: " << minResult << std::endl;

    std::string result;

    return 0;
}
