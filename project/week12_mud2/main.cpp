#include <iostream>
#include <string>
#include <vector>
#include "user.h"

using namespace std;

const int MAP_X = 5;
const int MAP_Y = 5;

// User 객체의 hp가 0인지 체크하는 함수
bool CheckUser(User user) {
    if (user.GetHP() <= 0) {
        return false;
    }
    return true;
}

// 2차원 벡터를 사용하는 지도 출력 함수
void displayMap(const vector<vector<int>>& map, int user_x, int user_y) {
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

// 2차원 벡터를 사용하는 목적지 도착 여부 확인 함수
bool checkGoal(const vector<vector<int>>& map, int user_x, int user_y) {
    return (map[user_x][user_y] == 4);
}

// 2차원 벡터를 사용하는 위치 이벤트 처리 함수
void checkState(vector<vector<int>>& map, int user_x, int user_y, User& user) {
    int posState = map[user_x][user_y];
    switch (posState) {
        case 1:
            cout << "아이템이 있습니다. 아이템을 획득합니다!" << endl;
            user.IncreaseItemCnt(); // 아이템 먹은 횟수 1 증가
            map[user_x][user_y] = 0; // 획득한 아이템은 맵에서 제거
            break;
        case 2:
            cout << "적이 있습니다. HP가 2 줄어듭니다." << endl;
            user.DecreaseHP(2);
            break;
        case 3:
            cout << "포션이 있습니다. HP가 2 늘어납니다." << endl;
            user.IncreaseHP(2);
            map[user_x][user_y] = 0; // 마신 포션은 맵에서 제거
            break;
    }
}

int main() {
    // 할 일 1: 맵 배열을 2차원 벡터(vector<vector<int>>)로 선언
    // 0: 빈 공간, 1: 아이템, 2: 적, 3: 포션, 4: 목적지
    vector<vector<int>> map = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    User user;

    int user_x = 0;
    int user_y = 0;

    while (true) {
        cout << "현재 HP: " << user.GetHP() << "  ";
        cout << "명령어를 입력하세요 (상,하,좌,우,지도,정보,종료): ";
        string user_input = "";
        cin >> user_input;

        if (user_input == "상") {
            user_x -= 1;
            if (!checkXY(user_x, MAP_X, user_y, MAP_Y)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                user_x += 1;
            } else {
                cout << "위로 한 칸 올라갑니다." << endl;
                user.DecreaseHP(1);
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
        } else if (user_input == "정보") {
            // 할 일 3-2: "정보" 입력 시 오버로딩된 << 연산자로 사용자 정보 출력
            cout << user << endl;
            continue; // 정보 확인 시에는 턴/HP 소모나 종료 판정을 건너뜀
        } else if (user_input == "종료") {
            cout << "종료합니다." << endl;
            break;
        } else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // HP 0 체크
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