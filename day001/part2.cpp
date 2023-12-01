#include <fstream>
#include <iostream>
#include <unordered_map>

const std::unordered_map<std::string, char> map = {
        {"zero",  '0'},
        {"one",   '1'},
        {"two",   '2'},
        {"three", '3'},
        {"four",  '4'},
        {"five",  '5'},
        {"six",   '6'},
        {"seven", '7'},
        {"eight", '8'},
        {"nine",  '9'}
};

int64_t line_to_digit(const std::string &pString) {
    // these get zero initialized
    static char num[3];
    static bool first_digit_found = false;
    for (size_t i = 0; i < pString.size(); ++i) {
        if (isdigit(pString[i])) {
            num[1] = pString[i];
            if (!first_digit_found) {
                first_digit_found = true;
                num[0] = pString[i];
            }
        } else {
            //Check the first three,four,and five characters and see if they're in the map
            for (int num_chars = 3; num_chars <= 5; num_chars++) {
                if (i + num_chars > pString.size()) {
                    break;
                }
                const auto substring = pString.substr(i, num_chars);
                auto it = map.find(substring);
                if (it != map.end()) {
                    num[1] = it->second;
                    if (!first_digit_found) {
                        first_digit_found = true;
                        num[0] = it->second;
                    }
                    break;
                }
            }
        }
    }
    return atoi(num);
}

int main() {
    // Open the file
    std::ifstream file("/Users/meow/CLionProjects/aoc1/input.txt");

    // Check if the file was opened successfully
    if (!file) {
        std::cerr << "Unable to open file input.txt" << std::endl;
        return 1;
    }

    std::string line;
    int64_t sum = 0;

    while (std::getline(file, line)) {
        auto result = line_to_digit(line);
        std::cout << "Input: " << line << " Result:";
        std::cout << result << '\n';
        sum += result;
    }

    // Close the file
    file.close();
    std::cout << sum << '\n';

    return 0;
}
