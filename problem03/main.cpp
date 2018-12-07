#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <limits>

struct Box
{
    size_t id;
    int x;
    int y;
    int w;
    int h;
};

std::ostream& operator<<(std::ostream& os, Box const& b) {
    os << "["
        << " id: " << b.id
        << " x: " << b.x
        << " y: " << b.y
        << " w: " << b.w
        << " h: " << b.h
        << " ]";

    return os;
}
void getId(Box& b, std::string const& id) {
    std::string tmp = id.substr(1);
    b.id = atoi(tmp.c_str());
}

void getPos(Box& b, std::string const& pos) {
    size_t comma = pos.find(',');
    size_t colon = pos.find(':');
    std::string x = pos.substr(0, comma);
    std::string y = pos.substr(comma+1, colon - (comma+1));
    b.x = atoi(x.c_str());
    b.y = atoi(y.c_str());
}

void getDim(Box& b, std::string const& dim) {
    size_t x = dim.find('x');
    std::string w = dim.substr(0, x);
    std::string h = dim.substr(x+1);
    b.w = atoi(w.c_str());
    b.h = atoi(h.c_str());
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "missing input file in arguments!" << std::endl;
        return 1;
    }

    std::string id;
    std::string at;
    std::string pos;
    std::string dim;

    typedef std::vector<Box> Boxes;
    Boxes boxes;
    int maxX = 0;
    int maxY = 0;
    std::ifstream inputFile(argv[1]);
    while (!inputFile.eof()) {
        inputFile >> id >> at >> pos >> dim;

        Box b;
        getId(b, id);
        getPos(b, pos);
        getDim(b, dim);

        std::cout << "Box: " << b << std::endl;

        boxes.push_back(b);

        maxX = std::max(maxX, b.x + b.w);
        maxY = std::max(maxY, b.y + b.h);
    }

    std::cout << "maxX: " << maxX << " maxY: " << maxY << std::endl;

    typedef std::vector<std::vector<char> > Mat;
    Mat mat;
    for (size_t i = 0; i < maxX; ++i) {
        mat.push_back(std::vector<char>(maxY, '.'));
    }

    for (Boxes::const_iterator it = boxes.begin(); it != boxes.end(); ++it) {
        for (int i = it->x; i < it->x + it->w; ++i) {
            for (int j = it->y; j < it->y + it->h; ++j) {
                mat[i][j] = mat[i][j] == '.' ? '#' : 'X';
            }
        }
    }

    int area = 0;
    for (Mat::const_iterator it = mat.begin(); it != mat.end(); ++it) {
        for (std::vector<char>::const_iterator jt = it->begin(); jt != it->end(); ++jt) {
            if (*jt == 'X') {
                ++area;
            }
        }
    }

    std::cout << "area: " << area << std::endl;

    for (Boxes::const_iterator it = boxes.begin(); it != boxes.end(); ++it) {
        bool clean = true;
        for (int i = it->x; i < it->x + it->w; ++i) {
            for (int j = it->y; j < it->y + it->h; ++j) {
                if (mat[i][j] == 'X') {
                    clean = false;
                }
            }
        }

        if (clean) {
            std::cout << "clean: " << it->id << std::endl;
        }
    }

    return 0;
}
