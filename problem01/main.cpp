#include <iostream>
#include <fstream>
#include <set>
#include <limits>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "missing input file in arguments!" << std::endl;
        return 1;
    }

    // PART 1 - find the final frequency from a list of frequency changes.
    std::ifstream inputFile(argv[1]);

    int change = 0;
    int freq = 0;
    while (inputFile >> change) {
        freq += change;
    }

    std::cout << "Final Frequency: " << freq << std::endl;

    // PART 2 - Do the same thing as above, but keep reading frequencies
    // until the first duplicate frequency is found.
    std::set<int> uniqueFreqs;
    bool found = false;

    freq = 0;
    uniqueFreqs.insert(freq);

    while (!found) {
        inputFile.clear();
        inputFile.seekg(0);

        while (inputFile >> change) {
            freq += change;
            std::pair<std::set<int>::iterator, bool> result = uniqueFreqs.insert(freq);
            if (result.second == false) {
                found = true;
                break;
            }
        }
    }

    std::cout << "First Duplicate: " << freq << std::endl;

    return 0;
}
