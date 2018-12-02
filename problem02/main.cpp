#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "missing input file in arguments!" << std::endl;
        return 1;
    }

    typedef std::vector<std::string> Lines;
    Lines lines;

    // PART 1 - Count strings that have either 2 or 3 of the same character in them.
    // Each count is then multiplied together to create our answer.
    int twos = 0;
    int threes = 0;

    std::ifstream inputFile(argv[1]);
    std::string line;
    while (!inputFile.eof()) {
        std::getline(inputFile, line);
        lines.push_back(line);

        typedef std::unordered_map<char, int> Counts;
        Counts counts;
        for (int i = 0; i < line.size(); ++i) {
            char c = line[i];
            Counts::iterator it = counts.find(c);
            if (it == counts.end()) {
                counts.insert(std::make_pair(c, 1));
            } else {
                it->second += 1;
            }
        }

        Counts::iterator it = counts.begin();
        bool foundTwos = false;
        bool foundThrees = false;
        while (it != counts.end()) {
            if (!foundTwos && it->second == 2) {
                foundTwos = true;
                ++twos;
            }
            if (!foundThrees && it->second == 3) {
                foundThrees = true;
                ++threes;
            }

            ++it;
        }
    }

    std::cout << "twos: " << twos << std::endl;
    std::cout << "threes: " << threes << std::endl;

    int result = twos * threes;

    std::cout << "result: " << result << std::endl;

    // PART 2 - find strings that only differ by one character.
    // Brute force, but gets the job done.
    for (Lines::iterator i = lines.begin(); i != lines.end(); ++i) {
        std::string first = *i;
        for (Lines::iterator j = lines.begin(); j != lines.end(); ++j) {
            std::string second = *j;

            int diff = 0;
            int pos = 0;
            for (int k = 0; k < first.size(); ++k) {
                if (first[k] != second[k]) {
                    ++diff;
                    pos = k;
                    if (diff > 1) {
                        break;
                    }
                }
            }

            if (diff == 1) {
                std::cout << first << std::endl;
                std::cout << second << std::endl;
                first.erase(pos, 1);

                std::cout << "ID: " << first << std::endl;
                return 0;
            }
        }
    }

    return 0;
}
