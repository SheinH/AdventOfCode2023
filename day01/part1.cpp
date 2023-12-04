#include <fstream>
#include <iostream>

enum State {
    fd,nl,ld
};
int main() {
    // Open the file
    std::ifstream file("input.txt");

    // Check if the file was opened successfully
    if (!file) {
        std::cerr << "Unable to open file input.txt" << std::endl;
        return 1;
    }

    char ch,num[3];
    num[2] = '\0';
    bool first_digit_found = false;
    int64_t sum = 0;
    while (file.get(ch)) {
        if(ch == '\n'){
            std::cout << num << '\n';
            sum += atoi(num);
            first_digit_found = false;
            continue;
        }
        if(isdigit(ch)){
            num[1] = ch;
            if(!first_digit_found){
                first_digit_found = true;
                num[0] = ch;
            }
        }
    }

    // Close the file
    file.close();
    std::cout << sum << '\n';

    return 0;
}
