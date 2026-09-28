#include <iostream>
#include <string> // [3인용 추가] △ 특수문자 처리를 위해 string 헤더 추가
using namespace std;

int main() {
    const int numCell = 3;
    string board[numCell][numCell]{}; // [3인용 수정] char -> string 변경
    int x,y; // 사용자에게 입력받는 x,y 좌표를 저장할 변수

    // 보드판 초기화
    for (x = 0; x < numCell; x++) {
        for (y = 0; y < numCell; y++) {
            board[x][y] = " "; // [3인용 수정] 공백 문자열로 초기화
        }
    }

// 게임하는 코드
    int k = 0; // 누구 차례인지 체크하기 위한 변수
    string currentUser = "X"; // [3인용 수정] 현재 유저의 돌을 저장하기 위한 string 변수
    while (true) {
        // 1. 누구 차례인지 출력 (3인용: k % 3 적용)
        switch (k % 3) { // [3인용 수정] % 2 -> % 3
        case 0:
            cout << k%3+1 <<"번 유저(X)의 차례입니다 -> ";
            currentUser = "X";
            break;
        case 1:
            cout << k%3+1 <<"번 유저(0)의 차례입니다 -> ";
            currentUser = "0";
            break;
        case 2: // [3인용 추가] 3번 유저(△) 차례 추가
            cout << k%3+1 <<"번 유저(△)의 차례입니다 -> ";
            currentUser = "△";
            break;
        }

        // 2. 좌표 입력 받기
        cout << "(x,y) 좌표를 입력하세요: ";
        cin >> x >> y;

        // 3. 입력받은 좌표의 유효성 체크
        if (x >= numCell || y >= numCell) {
            cout << x << ", " << y << ": ";
            cout << " x 와 y 둘 중 하나가 칸을 벗어납니다. " << endl;
            continue;
        }
        if (board[x][y] != " ") { // [3인용 수정] ' ' -> " "
            cout << x << ", " << y << ":이미 돌이 차있습니다." << endl;
            continue;
        }
            
        // 4. 입력받은 좌표에 현재 유저의 돌 놓기
        board[x][y] = currentUser;

        // 5. 현재 보드 판 출력
        for (int i = 0; i < numCell; i++) {
            cout << "---|---|---" << endl;
            for (int j = 0; j < numCell; j++){
                cout << board[i][j] << "  ";
                if (j == numCell - 1) {
                    break;
                }
                cout << "|";
            }
            cout << endl;
        }
        cout << "---|---|---" << endl;

        // ====================================================================
        // [추가 기능 1] 빙고 시 승자 출력 후 종료 (가로, 세로, 대각선)
        // ====================================================================
        bool isWin = false;

        // 1-1. 가로 검사
        for (int i = 0; i < numCell; i++) {
            if (board[i][0] == currentUser && board[i][1] == currentUser && board[i][2] == currentUser) {
                cout << "가로에 모두 돌이 놓였습니다!: " << k % 3 + 1 << "번 유저(" << currentUser << ")의 승리입니다!" << endl;
                cout << "종료합니다" << endl;
                isWin = true;
                break;
            }
        }

        // 1-2. 세로 검사
        if (!isWin) {
            for (int j = 0; j < numCell; j++) {
                if (board[0][j] == currentUser && board[1][j] == currentUser && board[2][j] == currentUser) {
                    cout << "세로에 모두 돌이 놓였습니다!: " << k % 3 + 1 << "번 유저(" << currentUser << ")의 승리입니다!" << endl;
                    cout << "종료합니다" << endl;
                    isWin = true;
                    break;
                }
            }
        }

        // 1-3. 대각선 검사 (왼쪽 위 -> 오른쪽 아래)
        if (!isWin && board[0][0] == currentUser && board[1][1] == currentUser && board[2][2] == currentUser) {
            cout << "왼쪽 위에서 오른쪽 아래 대각선으로 모두 돌이 놓였습니다!: " << k % 3 + 1 << "번 유저(" << currentUser << ")의 승리입니다!" << endl;
            cout << "종료합니다" << endl;
            isWin = true;
        }

        // 1-4. 대각선 검사 (오른쪽 위 -> 왼쪽 아래)
        if (!isWin && board[0][2] == currentUser && board[1][1] == currentUser && board[2][0] == currentUser) {
            cout << "오른쪽 위에서 왼쪽 아래 대각선으로 모두 돌이 놓였습니다!: " << k % 3 + 1 << "번 유저(" << currentUser << ")의 승리입니다!" << endl;
            cout << "종료합니다" << endl;
            isWin = true;
        }

        // 승리 조건 달성 시 게임 루프(while문) 종료
        if (isWin) {
            break;
        }

        // ====================================================================
        // [추가 기능 2] 모든 칸이 차면 종료
        // ====================================================================
        bool isFull = true;
        for (int i = 0; i < numCell; i++) {
            for (int j = 0; j < numCell; j++) {
                if (board[i][j] == " ") {
                    isFull = false;
                    break;
                }
            }
            if (!isFull) break;
        }

        if (isFull) {
            cout << "모든 칸이 다 찼습니다. 종료합니다" << endl;
            break;
        }

        k++;
    }
    return 0;
}