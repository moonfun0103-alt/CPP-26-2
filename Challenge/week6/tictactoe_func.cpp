#include <iostream> //[cite: 5]
using namespace std; //[cite: 5]

const int numCell = 3; //[cite: 5]
// 함수들에서 공통으로 접근할 수 있도록 보드판을 전역 변수로 선언합니다.
char board[numCell][numCell]{}; //[cite: 5]

// 1. 보드판 초기화 함수
void initBoard() {
    // x, y 루프를 돌며 모든 칸을 공백(' ')으로 초기화합니다[cite: 5].
    for (int x = 0; x < numCell; x++) { //[cite: 5]
        for (int y = 0; y < numCell; y++) { //[cite: 5]
            board[x][y] = ' '; //[cite: 5]
        }
    }
}

// 5. 현재 보드판 출력 함수
void printBoard() {
    for (int i = 0; i < numCell; i++) { //[cite: 5]
        cout << "---|---|---" << endl; //[cite: 5]
        for (int j = 0; j < numCell; j++) { //[cite: 5]
            cout << " " << board[i][j]; //[cite: 5]
            if (j == numCell - 1) { // 마지막 열이면 '|'를 출력하지 않고 루프를 빠져나감[cite: 5]
                break; //[cite: 5]
            }
            cout << " |"; //[cite: 5]
        }
        cout << endl; //[cite: 5]
    }
    cout << "---|---|---" << endl; //[cite: 5]
}

// 6. 모든 칸이 다 찼는지 체크하는 함수 (무승부 판별)
bool checkFull() {
    int checked = 0; //[cite: 5]
    for (int i = 0; i < numCell; i++) { //[cite: 5]
        for (int j = 0; j < numCell; j++) { //[cite: 5]
            if (board[i][j] == ' ') { // 보드판에 빈 칸(' ')이 하나라도 존재하면 checked 값을 증가[cite: 5]
                checked++; //[cite: 5]
            }
        }
    }
    // 빈 칸이 없어서 checked가 그대로 0이면 보드판이 꽉 찼다는 의미이므로 true 반환[cite: 5]
    return checked == 0; 
}

// 7. 승자 체크하기 함수
bool checkWin(char currentUser) {
    // 7.1. 가로/세로줄 체크하기[cite: 5]
    for (int i = 0; i < numCell; i++) { //[cite: 5]
        if (board[i][0] == currentUser && board[i][1] == currentUser && board[i][2] == currentUser) { //[cite: 5]
            cout << "가로에 모두 돌이 놓였습니다!: "; //[cite: 5]
            return true; // 승리 조건을 만족하면 true 반환
        }
        if (board[0][i] == currentUser && board[1][i] == currentUser && board[2][i] == currentUser) { //[cite: 5]
            cout << "세로에 모두 돌이 놓였습니다!: "; //[cite: 5]
            return true; 
        }
    }
    
    // 7.2. 대각선줄 체크하기[cite: 5]
    if (board[0][0] == currentUser && board[1][1] == currentUser && board[2][2] == currentUser) { //[cite: 5]
        cout << "왼쪽 위에서 오른쪽 아래 대각선으로 모두 돌이 놓였습니다!: "; //[cite: 5]
        return true;
    }
    if (board[0][2] == currentUser && board[1][1] == currentUser && board[2][0] == currentUser) { //[cite: 5]
        cout << "오른쪽 위에서 왼쪽 아래 대각선으로 모두 돌이 놓였습니다!: "; //[cite: 5]
        return true;
    }
    
    return false; // 위 조건을 아무것도 만족하지 않으면 승자가 없음
}

int main() {
    // 게임 시작 시 보드판을 먼저 초기화합니다.
    initBoard(); 
    
    int k = 0; // 누구 차례인지 체크하기 위한 변수[cite: 5]
    char currentUser = 'X'; // 현재 유저의 돌을 저장하기 위한 문자 변수[cite: 5]
    int x, y; // 사용자에게 입력받는 x, y 좌표를 저장할 변수[cite: 5]

    // 게임하는 코드 루프[cite: 5]
    while (true) { //[cite: 5]
        // 1. 누구 차례인지 출력[cite: 5]
        switch (k % 2) { // 짝수 턴은 X, 홀수 턴은 O[cite: 5]
            case 0: //[cite: 5]
                cout << "첫번째 유저(X)의 차례입니다 -> "; //[cite: 5]
                currentUser = 'X'; //[cite: 5]
                break; //[cite: 5]
            case 1: //[cite: 5]
                cout << "두번째 유저(O)의 차례입니다 -> "; //[cite: 5]
                currentUser = 'O'; //[cite: 5]
                break; //[cite: 5]
        }

        // 2. 좌표 입력 받기[cite: 5]
        cout << "(x, y) 좌표를 입력하세요: "; //[cite: 5]
        cin >> x >> y; //[cite: 5]

        // 3. 입력받은 좌표의 유효성 체크[cite: 5]
        // 미완성 보완: 원본 코드에는 없지만 x < 0 또는 y < 0 등 음수를 입력했을 때 배열 인덱스가 꼬이는 것을 방지하기 위해 범위를 정확하게 제한했습니다.
        if (x < 0 || x >= numCell || y < 0 || y >= numCell) { 
            cout << x << ", " << y << ": "; //[cite: 5]
            cout << "x 와 y 둘 중 하나가 칸을 벗어납니다." << endl; //[cite: 5]
            continue; // 잘못된 입력이므로 루프를 건너뛰고 다시 입력받음[cite: 5]
        }
        if (board[x][y] != ' ') { // 해당 칸이 공백이 아니라면 이미 돌이 놓인 상태[cite: 5]
            cout << x << ", " << y << ": 이미 돌이 차있습니다." << endl; //[cite: 5]
            continue; //[cite: 5]
        }

        // 4. 입력받은 좌표에 현재 유저의 돌 놓기[cite: 5]
        board[x][y] = currentUser; //[cite: 5]

        // 5. 현재 보드 판 출력 함수를 호출하여 화면에 갱신된 보드를 그립니다.
        printBoard();

        // 7. 승자 체크하기
        if (checkWin(currentUser)) { //[cite: 5]
            cout << (k % 2) + 1 << "번 유저(" << currentUser << ")의 승리입니다!" << endl; //[cite: 5]
            cout << "종료합니다" << endl; //[cite: 5]
            break; // 승자가 정해졌으므로 게임 루프를 종료합니다[cite: 5].
        }

        // 6. 모든 칸 다 찼는지 체크하기
        if (checkFull()) { //[cite: 5]
            cout << "모든 칸이 다 찼습니다. 종료합니다" << endl; // 무승부 처리[cite: 5]
            break; //[cite: 5]
        }

        // 턴을 넘기기 위해 k값을 증가시킵니다.
        k++; //[cite: 5]
    }
    return 0; //[cite: 5]
}