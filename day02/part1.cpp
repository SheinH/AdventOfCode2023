#include <iostream>
#include <fstream>

#define INPUT_FILE "input.txt"


bool check_round(std::ifstream &input) {
    int red, blue, green;
    red = blue = green = 0;
    while (input.peek() != ';') {
        int num;
        char color;
        input >> num;
        input.ignore(1);
        input >> color;
        switch (color) {
            case 'r':
                red += num;
                input.ignore(2);
                break;
            case 'g':
                green += num;
                input.ignore(4);
                break;
            case 'b':
                blue += num;
                input.ignore(3);
                break;
            default:
                return false;
        }
        char peek = input.peek();
        if (input.peek() == ',') {
            input.ignore(2);
        } else {
            break;
        }
    }

    std::cout << "Red: " << red << ", Green: " << green << ", Blue: " << blue << std::endl;

    return red <= 12 && green <= 13 && blue <= 14;
}

int check_game(std::ifstream &input) {
    if (input.peek() != 'G') {
        input.close();
        return 0;
    }
    input.ignore(5);
    int game_num;
    input >> game_num;
    input.ignore(2);
    bool has_next = true;
    while (has_next) {
        bool result = check_round(input);
        if (!result) {
            while (input.peek() != '\n') {
                input.ignore(1);
            }
            input.ignore(1);
            return 0;
        }
        while (input.peek() != '\n' && !isdigit(input.peek())) {
            input.ignore(1);
        }
        if (input.peek() == '\n') {
            input.ignore(1);
            break;
        }
    }
    return game_num;
}

int main() {
    std::ifstream file("/Users/meow/CLionProjects/aoc2/inputd2.txt");

    // Check if the file was opened successfully
    if (!file) {
        std::cerr << "Unable to open file input.txt" << std::endl;
        return 1;
    }
    int sum;

    while (file.is_open()) {
        sum += check_game(file);
    }
    std::cout << "Total: " << sum;

    return 0;

}
