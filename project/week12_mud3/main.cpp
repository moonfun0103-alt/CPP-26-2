#include <iostream>
#include <string>
#include <vector>
#include "user.h"

using namespace std;

const int MAP_X = 5;
const int MAP_Y = 5;

// User 객체의 hp가 0인지 체크하는 함수
bool CheckUser(const User& user) {
    if (user.GetHP() <= 0) {
        return false;
    }
    return true;
}

// 두 유저(Magician, Warrior)의 위치를 모두 표시하는 지도 출력 함수
void displayMap(const vector<vector<int>>& map, int mag_x, int mag_y, int war_x, int war_y) {
    for (int i = 0; i < MAP_X; i++) {
        for (int j = 0; j < MAP_Y; j++) {
            if (i == mag_x && j == mag_y && i == war_x && j == war_y) {
                cout << " BOTH |";
            } else if (i == mag_x && j == mag_y) {
                cout << " MAGI |";
            } else if (i == war_x && j == war_y) {
                cout << " WARR |";
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
bool checkGoal(const vector<vector<int>>& map, int user_x, int user_y) {
    return (map[user_x][user_y] == 4);
}

// 위치 이벤트 처리 함수 (다형성을 위해 User& 참조로 받음)
void checkState(vector<vector<int>>& map, int user_x, int user_y, User& user) {
    int posState = map[user_x][user_y];
    switch (posState) {
        case 1:
            cout << "아이템이 있습니다. 아이템을 획득합니다!" << endl;
            user.IncreaseItemCnt();
            map[user_x][user_y] = 0;
            break;
        case 2:
            cout << "적이 있습니다! ";
            user.doAttack(); // Magician이면 "마법 사용", Warrior면 "베기 사용" 출력
            cout << "전투 여파로 HP가 2 줄어듭니다." << endl;
            user.DecreaseHP(2);
            break;
        case 3:
            cout << "포션이 있습니다. HP가 2 늘어납니다." << endl;
            user.IncreaseHP(2);
            map[user_x][user_y] = 0;
            break;
    }
}

int main() {
    // 0: 빈 공간, 1: 아이템, 2: 적, 3: 포션, 4: 목적지
    vector<vector<int>> map = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    // Magician과 Warrior 두 명의 유저 생성
    Magician magician;
    Warrior warrior;

    int mag_x = 0, mag_y = 0;
    int war_x = 0, war_y = 0;

    int turn = 0; // 0: Magician 차례, 1: Warrior 차례

    while (true) {
        // 현재 차례인 유저의 포인터와 좌표 참조 연결
        User* currentUser = (turn == 0) ? static_cast<User*>(&magician) : static_cast<User*>(&warrior);
        int& cur_x = (turn == 0) ? mag_x : war_x;
        int& cur_y = (turn == 0) ? mag_y : war_y;
        string roleName = (turn == 0) ? "Magician" : "Warrior";

        cout << "\n[" << roleName << "의 차례] 현재 HP: " << currentUser->GetHP() << "  ";
        cout << "명령어를 입력하세요 (상,하,좌,우,지도,정보,종료): ";
        string user_input = "";
        cin >> user_input;

        if (user_input == "상") {
            cur_x -= 1;
            if (!checkXY(cur_x, MAP_X, cur_y, MAP_Y)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                cur_x += 1;
                continue; // 잘못된 이동 시 턴을 넘기지 않고 다시 입력받음
            }
            cout << "위로 한 칸 올라갑니다." << endl;
            currentUser->DecreaseHP(1);
            displayMap(map, mag_x, mag_y, war_x, war_y);
            checkState(map, cur_x, cur_y, *currentUser);

        } else if (user_input == "하") {
            cur_x += 1;
            if (!checkXY(cur_x, MAP_X, cur_y, MAP_Y)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                cur_x -= 1;
                continue;
            }
            cout << "아래로 한 칸 내려갑니다." << endl;
            currentUser->DecreaseHP(1);
            displayMap(map, mag_x, mag_y, war_x, war_y);
            checkState(map, cur_x, cur_y, *currentUser);

        } else if (user_input == "좌") {
            cur_y -= 1;
            if (!checkXY(cur_x, MAP_X, cur_y, MAP_Y)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                cur_y += 1;
                continue;
            }
            cout << "왼쪽으로 이동합니다." << endl;
            currentUser->DecreaseHP(1);
            displayMap(map, mag_x, mag_y, war_x, war_y);
            checkState(map, cur_x, cur_y, *currentUser);

        } else if (user_input == "우") {
            cur_y += 1;
            if (!checkXY(cur_x, MAP_X, cur_y, MAP_Y)) {
                cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
                cur_y -= 1;
                continue;
            }
            cout << "오른쪽으로 이동합니다." << endl;
            currentUser->DecreaseHP(1);
            displayMap(map, mag_x, mag_y, war_x, war_y);
            checkState(map, cur_x, cur_y, *currentUser);

        } else if (user_input == "지도") {
            displayMap(map, mag_x, mag_y, war_x, war_y);
            continue; // 지도 확인은 턴 유지

        } else if (user_input == "정보") {
            cout << "[" << roleName << "] " << *currentUser << endl;
            continue; // 정보 확인은 턴 유지

        } else if (user_input == "종료") {
            cout << "게임을 종료합니다." << endl;
            break;

        } else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // HP 0 체크
        if (!CheckUser(*currentUser)) {
            cout << roleName << "의 HP가 0 이하가 되었습니다. 실패했습니다!" << endl;
            cout << "게임을 종료합니다." << endl;
            break;
        }

        // 목적지 도달 체크
        if (checkGoal(map, cur_x, cur_y)) {
            cout << roleName << "이(가) 목적지에 먼저 도착했습니다! 승리했습니다!" << endl;
            cout << "게임을 종료합니다." << endl;
            break;
        }

        // 다음 유저로 턴 교체 (0 -> 1, 1 -> 0)
        turn = 1 - turn;
    }

    return 0;
}