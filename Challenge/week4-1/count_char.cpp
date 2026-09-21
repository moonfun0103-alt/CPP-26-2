#include <iostream>
using namespace std;

int main(){
    int vowel = 0;
    int consonant = 0;
    cout << "영문자를 입력하고 엔터치고, ctrl+z를 치세요" << endl;

    char ch; // 사용자 입력 저장하기 위한 변수

    //HINT: WHILE + switch 문 활용

    while (cin >> ch){
        switch(ch){
            case 'a':
            case 'i':
            case 'e':
            case 'o':
            case 'u':
            case 'A':
            case 'I':
            case 'E':
            case 'O':
            case 'U':
                vowel++;
                break;
            default:
                consonant++;

        }
    }

    cout << "모음: " << vowel << endl;
    cout << "자음: " << consonant << endl;
    return 0;
}