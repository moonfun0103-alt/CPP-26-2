#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main() {
    int numCell = 10;
    int numList[numCell][numCell];

    // 1. 2차원 배열에 난수 저장 및 출력하는 코드 (이중 for문)
    srand(time(NULL)); // 난수 생성을 위한 시드 설정
    for (int i = 0; i < numCell; i++) {
        for (int j = 0; j < numCell; j++) {
            numList[i][j] = rand() % 1000; // 0 ~ 999 사이의 난수 저장
            cout << i << ", " << j << " : " << numList[i][j] << endl;
        }
    }

    cout << endl;

    int max;
    int maxI;
    int maxJ;

    // 2. 큰 값과 그 위치를 찾는 코드 (이중 for문)
    max = numList[0][0];
    maxI = 0;
    maxJ = 0;
    
    for (int i = 0; i < numCell; i++) {
        for (int j = 0; j < numCell; j++) {
            if (numList[i][j] > max) {
                max = numList[i][j];
                maxI = i;
                maxJ = j;
            }
        }
    }

    cout << " 가장 큰 값은 " << max << "이고,";
    cout << " i와 j는 각각 " << maxI <<", "<< maxJ << "입니다." << endl;
    cout << " 검증결과: " << numList[maxI][maxJ] << endl;

    return 0;
}