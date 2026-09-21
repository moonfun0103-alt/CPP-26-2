#include <iostream>

int main() {
    int number1, number2;

    std::cout << "두 양수를 입력하세요: ";
    std::cin >> number1 >> number2;

    if (number1 > 0) {
        if (number2 > 0) {
            std::cout << number1 << ", " << number2 << " 두 숫자 모두 양수입니다.\n";
        }
        else {
            std::cout << number1 << " 만 양수입니다.\n";
        }
    }
    else {
        std::cout << number1 << " 는 0이거나 음수입니다.\n";
    }

    return 0;
}