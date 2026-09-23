#include <iostream>
#include <string>
using namespace std;

int main() {
    int maxPeople;
    cout << "총 고객의 수를 입력하라: ";
    cin >> maxPeople;
    string names[maxPeople];
    int ages[maxPeople];

    // 1. 고객의 이름과 나이를 입력 받는 코드
    for (int i = 0; i < maxPeople; i++) {
        cout << "사람 " << i + 1 << "의 이름: ";
        cin >> names[i];
        cout << "사람 " << i + 1 << "의 나이: ";
        cin >> ages[i];
    }

    int ageThreshold;
    cout << "특정 나이 이상인 사람을 찾으려면 나이를 입력하세요: ";
    cin >> ageThreshold;

    cout << ageThreshold << "세 이상인 고객들:\n";

    // 2. ageThreshold 이상인 고객 이름 (나이) 출력 코드
    int matchCount = 0;
    for (int i = 0; i < maxPeople; i++) {
        if (ages[i] >= ageThreshold) {
            cout << names[i] << " (" << ages[i] << "세)\n";
            matchCount++;
        }
    }

    // 3. 특정 나이보다 많은 고객이 없는 경우 메시지 출력 코드
    if (matchCount == 0) {
        cout << ageThreshold << "이상의 나이를 가진 고객이 없습니다\n";
    }

    return 0;
}