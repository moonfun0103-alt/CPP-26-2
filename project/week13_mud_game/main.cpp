#include <iostream>
#include <string>
#include <vector>
#include "user.h"
using namespace std;

const int mapX = 5;
const int mapY = 5;

// 사용자 정의 함수 선언
bool checkXY(int user_x, int mapX, int user_y, int mapY);
void displayMap(vector<vector<int>> map, int user_x, int user_y);
bool checkGoal(vector<vector<int>> map, int user_x, int user_y);
void checkState(vector<vector<int>> map, int user_x, int user_y, User* user);
bool CheckUser(User* user);

int main() {
    // 0은 빈 공간, 1은 아이템, 2는 적, 3은 포션, 4는 목적지
    vector<vector<int>> map = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    // 2. 게임 시작 시 직업 선택 및 상향 형변환
    User* user = nullptr;
    int job_choice = 0;

    while (true) {
        cout << "직업을 선택하세요 (1: Magician, 2: Warrior): ";
        cin >> job_choice;
        if (job_choice == 1) {
            user = new Magician(); // 상향 형변환 (Upcasting)
            cout << "Magician을 선택했습니다." << endl;
            break;
        }
        else if (job_choice == 2) {
            user = new Warrior();  // 상향 형변환 (Upcasting)
            cout << "Warrior를 선택했습니다." << endl;
            break;
        }
        else {
            cout << "잘못된 입력입니다. 1 또는 2를 입력하세요." << endl;
        }
    }

    // 한 유저만 게임 진행 (시작 위치: 0, 0)
    int user_x = 0;
    int user_y = 0;

    while (true) {
        string user_input = "";
        cout << "현재 HP: " << user->GetHP() << "  명령어를 입력하세요 (상,하,좌,우,지도,공격,종료): ";
        cin >> user_input;

        if (user_input == "상") {
            user_y -= 1;
            if (!checkXY(user_x, mapX, user_y, mapY)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_y += 1;
            }
            else {
                cout << "위로 한 칸 올라갑니다." << endl;
                user->DecreaseHP(1);
                displayMap(map, user_x, user_y);
                checkState(map, user_x, user_y, user);
            }
        }
        else if (user_input == "하") {
            user_y += 1;
            if (!checkXY(user_x, mapX, user_y, mapY)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_y -= 1;
            }
            else {
                cout << "아래로 한 칸 내려갑니다." << endl;
                user->DecreaseHP(1);
                displayMap(map, user_x, user_y);
                checkState(map, user_x, user_y, user);
            }
        }
        else if (user_input == "좌") {
            user_x -= 1;
            if (!checkXY(user_x, mapX, user_y, mapY)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_x += 1;
            }
            else {
                cout << "왼쪽으로 이동합니다." << endl;
                user->DecreaseHP(1);
                displayMap(map, user_x, user_y);
                checkState(map, user_x, user_y, user);
            }
        }
        else if (user_input == "우") {
            user_x += 1;
            if (!checkXY(user_x, mapX, user_y, mapY)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_x -= 1;
            }
            else {
                cout << "오른쪽으로 이동합니다." << endl;
                user->DecreaseHP(1);
                displayMap(map, user_x, user_y);
                checkState(map, user_x, user_y, user);
            }
        }
        else if (user_input == "지도") {
            displayMap(map, user_x, user_y);
        }
        else if (user_input == "공격") {
            // 다형성에 의해 실제 객체(Magician 또는 Warrior)의 DoAttack() 호출
            user->DoAttack();
        }
        else if (user_input == "종료") {
            cout << "게임을 종료합니다." << endl;
            break;
        }
        else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // HP가 0 이하인지 확인
        if (!CheckUser(user)) {
            cout << "HP가 0 이하가 되었습니다. 실패했습니다. 게임을 종료합니다." << endl;
            break;
        }

        // 목적지 도착 확인
        if (checkGoal(map, user_x, user_y)) {
            cout << "목적지에 도착했습니다! 축하합니다!" << endl;
            cout << "게임을 종료합니다." << endl;
            break;
        }
    }

    // 동적 할당 메모리 해제
    delete user;
    return 0;
}

// 지도 및 사용자 위치 출력 함수
void displayMap(vector<vector<int>> map, int user_x, int user_y) {
    for (int i = 0; i < mapY; i++) {
        for (int j = 0; j < mapX; j++) {
            if (i == user_y && j == user_x) {
                cout << " USER |";
            }
            else {
                int posState = map[i][j];
                switch (posState) {
                case 0:
                    cout << "      |";
                    break;
                case 1:
                    cout << "아이템|";
                    break;
                case 2:
                    cout << "  적  |";
                    break;
                case 3:
                    cout << " 포션 |";
                    break;
                case 4:
                    cout << "목적지|";
                    break;
                }
            }
        }
        cout << endl;
        cout << " -------------------------------- " << endl;
    }
}

// 이동하려는 좌표가 유효한 좌표인지 체크하는 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY) {
    return (user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY);
}

// 유저의 위치가 목적지인지 체크하는 함수
bool checkGoal(vector<vector<int>> map, int user_x, int user_y) {
    return (map[user_y][user_x] == 4);
}

// 현재 위치의 상태(아이템, 적, 포션)에 따라 처리하는 함수
void checkState(vector<vector<int>> map, int user_x, int user_y, User* user) {
    int posState = map[user_y][user_x];
    if (posState == 1) {
        cout << "아이템이 있습니다." << endl;
    }
    else if (posState == 2) {
        cout << "적이 있습니다. HP가 2 줄어듭니다." << endl;
        user->DecreaseHP(2);
    }
    else if (posState == 3) {
        cout << "포션이 있습니다. HP가 2 늘어납니다." << endl;
        user->IncreaseHP(2);
    }
}

// 유저의 HP가 0 초과인지 확인하는 함수
bool CheckUser(User* user) {
    return (user->GetHP() > 0);
}