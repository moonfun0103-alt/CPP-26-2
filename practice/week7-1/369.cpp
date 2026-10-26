#include <iostream>
using namespace std;

int main() {
    int max_num = 50; // 50까지 진행 (Python: max_num = 50)

    // Python: for i in range(1, max_num + 1):
    for (int i = 1; i <= max_num; i++) {
        int temp = i; // 원본 숫자 보존 (Python: temp = i)
        int clap = 0; // 박수 횟수 초기화 (매 숫자마다 0으로 리셋 필수)

        // [핵심 로직] 자릿수 분리하기 (빈칸 단골 문제)
        // 더 이상 나눌 자릿수가 없을 때까지(0보다 클 때까지) 반복
        // Python: while temp > 0:
        while (temp > 0) {
            // 1. 일의 자리 추출: 10으로 나눈 나머지 구하기 (예: 36 % 10 = 6)
            // Python: digit = temp % 10
            int digit = temp % 10; 
            
            // 2. 3, 6, 9 확인
            // Python: if digit == 3 or digit == 6 or digit == 9:
            if (digit == 3 || digit == 6 || digit == 9) {
                clap++; // 박수 횟수 증가 (Python: clap += 1)
            }
            
            // 3. 다음 자릿수로 이동: 10으로 나눈 몫 저장 (예: 36 / 10 = 3)
            // [주의] C++의 정수형 나눗셈(/)은 소수점을 알아서 버림
            // Python: temp //= 10 (파이썬의 몫 구하기와 완벽히 동일)
            temp /= 10; 
        }

        // 박수를 쳐야 하는 경우
        // Python: if clap > 0:
        if (clap > 0) {
            // Python: print("짝" * clap, end=" ")
            for (int k = 0; k < clap; k++) cout << "짝";
            cout << " ";
        } else {
            // 3, 6, 9가 없으면 원래 숫자 출력
            // Python: print(i, end=" ")
            cout << i << " ";
        }
    }
    return 0;
}