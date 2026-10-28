#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    vector<int> grades;
    int score;
    int sum = 0;

    while (true) {
        cout << "성적을 입력하시오(종료는 -1) : ";
        cin >> score;

        // -1이 입력되면 입력을 종료합니다.
        if (score == -1) {
            break;
        }

        grades.push_back(score);
    }

    // 벡터가 비어있지 않은 경우에만 평균을 계산합니다.
    if (!grades.empty()) {
        for (int g : grades) {
            sum += g;
        }
        
        int average = sum / grades.size();
        cout << "성적 평균=" << average << endl;
    }

    return 0;
}