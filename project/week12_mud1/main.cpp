#include <iostream>
#include <string>
#include "user.h"

using namespace std;

const int MAP_X = 5;
const int MAP_Y = 5;

// 조건 5: User 객체의 hp가 0인지 체크하는 함수
bool CheckUser(User user) {
    if (user.GetHP() <= 0) {
        return false;
    }
    return true;
}

// 지도 출력 함수
void displayMap(int map[][MAP_Y], int user_x, int user_y) {
    for (int i = 0; i < MAP_X; i++) {
        for (int j = 0; j < MAP_Y; j++) {
            if (i == user_x && j == user_y) {
                cout << " USER |";
            } else {
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
        cout << " ----------------------------------" << endl;
    }
}

// 이동 유효성 검사 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY) {
    return (user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY);
}

// 목적지 도착 여부 확인 함수
bool checkGoal(int map[][MAP_Y], int user_x, int user_y) {
    return (map[user_x][user_y] == 4);
}

// 위치 이벤트 처리 함수 (HP 증감에 User 객체 멤버함수 활용)
void checkState(int map[][MAP_Y], int user_x, int user_y, User& user) {
    int posState = map[user_x][user_y];
    switch (posState) {
        case 1:
            cout << "아이템이 있습니다." << endl;
            break;
        case 2:
            cout << "적이 있습니다. HP가 2 줄어듭니다." << endl;
            user.DecreaseHP(2); // 조건 2: DecreaseHP 호출
            break;
        case 3:
            cout << "포션이 있습니다. HP가 2 늘어납니다." << endl;
            user.IncreaseHP(2); // 조건 4: 물약 섭취 시 HP 2 증가
            break;
    }
}

int main() {
    // 0: 빈 공간, 1: 아이템, 2: 적, 3: 포션, 4: 목적지
    int map[MAP_X][MAP_Y] = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    // 조건 1: 단일 유저 객체 생성 (생성자에 의해 hp = 20 초기화)
    User user;

    int user_x = 0;
    int user_y = 0;

    while (true) {
        // 조건 3: GetHP() 멤버 함수를 호출하여 현재 HP 출력
        cout << "현재 HP: " << user.GetHP() << "  ";
        cout << "명령어를 입력하세요 (상,하,좌,우,지도,종료): ";
        string user_input = "";
        cin >> user_input;

        if (user_input == "상") {
            user_x -= 1;
            if (!checkXY(user_x, MAP_X, user_y, MAP_Y)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_x += 1;
            } else {
                cout << "위로 한 칸 올라갑니다." << endl;
                user.DecreaseHP(1); // 조건 2: 이동 시 HP 1 감소
                displayMap(map, user_x, user_y);
                checkState(map, user_x, user_y, user);
            }
        } else if (user_input == "하") {
            user_x += 1;
            if (!checkXY(user_x, MAP_X, user_y, MAP_Y)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_x -= 1;
            } else {
                cout << "아래로 한 칸 내려갑니다." << endl;
                user.DecreaseHP(1);
                displayMap(map, user_x, user_y);
                checkState(map, user_x, user_y, user);
            }
        } else if (user_input == "좌") {
            user_y -= 1;
            if (!checkXY(user_x, MAP_X, user_y, MAP_Y)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_y += 1;
            } else {
                cout << "왼쪽으로 이동합니다." << endl;
                user.DecreaseHP(1);
                displayMap(map, user_x, user_y);
                checkState(map, user_x, user_y, user);
            }
        } else if (user_input == "우") {
            user_y += 1;
            if (!checkXY(user_x, MAP_X, user_y, MAP_Y)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_y -= 1;
            } else {
                cout << "오른쪽으로 이동합니다." << endl;
                user.DecreaseHP(1);
                displayMap(map, user_x, user_y);
                checkState(map, user_x, user_y, user);
            }
        } else if (user_input == "지도") {
            displayMap(map, user_x, user_y);
        } else if (user_input == "종료") {
            cout << "종료합니다." << endl;
            break;
        } else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // 조건 6: CheckUser() 함수를 적절한 위치에서 사용하여 HP 0 체크
        if (!CheckUser(user)) {
            cout << "HP가 0 이하가 되었습니다. 실패했습니다." << endl;
            cout << "게임을 종료합니다." << endl;
            break;
        }

        // 목적지 도달 체크
        if (checkGoal(map, user_x, user_y)) {
            cout << "목적지에 도착했습니다! 축하합니다!" << endl;
            cout << "게임을 종료합니다." << endl;
            break;
        }
    }

    return 0;
}