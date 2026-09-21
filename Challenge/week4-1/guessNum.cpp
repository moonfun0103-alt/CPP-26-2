#include <iostream>
#include <time.h>
using namespace std;

int main(){
    srand(time(NULL)); // random 함수 관련 설정

    int answer = rand() % 100;
    int tries = 0; 

    int guess;

    // HINT: while / do-while 문
    while(true){
        cin >> guess;

        if(guess > answer){
            cout << "제시한 정수가 답보다 큽니다." << endl;
        }else if(guess < answer){
            cout << "제시한 정수가 답보다 작습니다." << endl;
        }else{
            cout << "제시한 정수와 답이 같습니다." << endl;
        }
        tries++;

        if(guess == answer)
            break;
    }

    cout << "축하합니다. 시도 횟수 = " << tries << endl;
    return 0;

}