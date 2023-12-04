#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>

#define INPUT_FILE "/Users/meow/CLionProjects/aoc3/input.txt"


struct Coord {
    int x, y;

    Coord(int x, int y) : x(x), y(y) {}

    bool operator==(const Coord &other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template<>
    struct hash<Coord> {
        size_t operator()(const Coord &coord) const {
            size_t h1 = hash<int>()(coord.x);
            size_t h2 = hash<int>()(coord.y);
            return h1 ^ (h2 << 1); // Shift and XOR for better hash distribution
        }
    };
}

long
process_symbol(const std::vector<std::string> &vector, std::unordered_set<Coord> &visited, int y, int x, int w, int h) {
    long sum = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            int x2 = x + dx;
            int y2 = y + dy;
            if (x2 < 0 || x2 >= w) {
                continue;
            }
            if (y2 < 0 || y2 >= h) {
                continue;
            }
            char c = vector[y2][x2];
            if (!isdigit(c)) {
                continue;
            }
            Coord coord = {x2, y2};
            if (visited.find(coord) != visited.end()) {
                continue;
            }
            //Scan left and right for digits
            int left = x2, right = x2;
            while (left >= 0 && isdigit(vector[y2][left])) {
                left--;
            }
            left++;
            while (right < w && isdigit(vector[y2][right])) {
                right++;
            }
            for (int x3 = left; x3 < right; x3++) {
                Coord c = {x3, y2};
                visited.insert(c);
            }
            auto substring = vector[y2].substr(left, right - left);
            int num = std::stoi(substring);
            sum += num;
            std::cout << "Num: " << num << '\n';
        }
    }
    return sum;
}

long process_numbers(const std::vector<std::string> &lines) {
    int w = lines.size(), h = lines[0].size();
    std::unordered_set<Coord> visited;
    long sum = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; ++x) {
            char c = lines[y][x];
            if (!isdigit(c) && c != '.') {
                //Found a symbol
                sum += process_symbol(lines, visited, y, x, w, h);
            }
        }
    }
    std::cout << sum;
    return sum;
}

int main() {
    std::ifstream file(INPUT_FILE);
    std::vector<std::string> lines;
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file\n";
        return 1;
    }
    process_numbers(lines);


    return 0;
}
