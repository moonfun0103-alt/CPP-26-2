#include <iostream>
#include <string>
using namespace std;

const int mapX = 5;
const int mapY = 5;

// 사용자 정의 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY);
void displayMap(int map[][mapX], int user_x, int user_y);
bool checkGoal(int map[][mapX], int user_x, int user_y);
// 추가된 함수: 이동 위치를 계산하고 유효성을 검증하는 함수[cite: 1]
bool moveUser(int &user_x, int &user_y, int dx, int dy, int mapX, int mapY);
// 추가된 함수: 위치 이동 후 발생하는 이벤트를 처리하는 함수[cite: 1]
void checkEvent(int map[][mapX], int user_x, int user_y, int &hp);

// 메인 함수
int main()
{
	// 0은 빈 공간, 1은 아이템, 2는 적, 3은 포션, 4는 목적지
	int map[mapY][mapX] = {{0, 1, 2, 0, 4},
						   {1, 0, 0, 2, 0},
						   {0, 0, 0, 0, 0},
						   {0, 2, 3, 0, 0},
						   {3, 0, 0, 0, 2}};

	// 유저의 위치를 저장할 변수
	int user_x = 0; // 가로 번호
	int user_y = 0; // 세로 번호

	// 유저의 체력 설정 (요구사항 1)[cite: 1]
	int hp = 20;

	// 게임 시작
	while (1)
	{
		// 체력이 0 이하가 되면 게임 오버 처리 (요구사항 4)[cite: 1]
		if (hp <= 0)
		{
			cout << "실패" << endl;
			break;
		}

		string user_input = "";

		// 명령문 입력 시 현재 HP 출력 (요구사항 3)[cite: 1]
		cout << "현재 HP: " << hp << " | 명령어를 입력하세요 (상,하,좌,우,지도,종료): ";
		cin >> user_input;

		bool isMoved = false;

		if (user_input == "상")
		{
			isMoved = moveUser(user_x, user_y, 0, -1, mapX, mapY);
			if (isMoved)
				cout << "위로 한 칸 올라갑니다." << endl;
		}
		else if (user_input == "하")
		{
			isMoved = moveUser(user_x, user_y, 0, 1, mapX, mapY);
			if (isMoved)
				cout << "아래로 한 칸 내려갑니다." << endl;
		}
		else if (user_input == "좌")
		{
			isMoved = moveUser(user_x, user_y, -1, 0, mapX, mapY);
			if (isMoved)
				cout << "왼쪽으로 이동합니다." << endl;
		}
		else if (user_input == "우")
		{
			isMoved = moveUser(user_x, user_y, 1, 0, mapX, mapY);
			if (isMoved)
				cout << "오른쪽으로 이동합니다." << endl;
		}
		else if (user_input == "지도")
		{
			displayMap(map, user_x, user_y);
			continue; // 지도를 볼 때는 체력이 깎이지 않도록 continue 사용
		}
		else if (user_input == "종료")
		{
			cout << "종료합니다.";
			break;
		}
		else
		{
			cout << "잘못된 입력입니다." << endl;
			continue;
		}

		// 이동을 성공적으로 완료했을 때 체력 차감 및 이벤트 처리[cite: 1]
		if (isMoved)
		{
			hp -= 1; // 이동할 때마다 체력 1 감소 (요구사항 2)[cite: 1]
			displayMap(map, user_x, user_y);
			checkEvent(map, user_x, user_y, hp); // 맵 타일에 따른 이벤트 처리 (요구사항 5)[cite: 1]
		}

		// 체력 감소 후 사망 체크 (요구사항 4)[cite: 1]
		if (hp <= 0)
		{
			cout << "실패" << endl;
			break;
		}

		// 목적지에 도달했는지 체크
		if (checkGoal(map, user_x, user_y))
		{
			cout << "목적지에 도착했습니다! 축하합니다!" << endl;
			cout << "게임을 종료합니다." << endl;
			break;
		}
	}
	return 0;
}

// 이동하려는 곳이 유효한 좌표인지 체크하고, 유효하지 않으면 롤백하는 함수 (코드 최적화)[cite: 1]
bool moveUser(int &user_x, int &user_y, int dx, int dy, int mapX, int mapY)
{
	user_x += dx;
	user_y += dy;

	bool inMap = checkXY(user_x, mapX, user_y, mapY);
	if (!inMap)
	{
		cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
		user_x -= dx;
		user_y -= dy;
		return false;
	}
	return true;
}

// 각 타일 위치에 대한 이벤트(메시지 출력 및 HP 변동)를 처리하는 함수 (요구사항 5)[cite: 1]
// 각 타일 위치에 대한 이벤트(메시지 출력 및 HP 변동)를 처리하는 함수
void checkEvent(int map[][mapX], int user_x, int user_y, int &hp)
{
	int posState = map[user_y][user_x];
	if (posState == 1)
	{
		cout << "아이템(무기/갑옷)이 있습니다." << endl;
	}
	else if (posState == 2)
	{
		cout << "적이 있습니다. 추가로 HP가 2 줄어듭니다." << endl;
		hp -= 2;
	}
	else if (posState == 3)
	{
		cout << "포션을 마셨습니다! HP가 5 회복됩니다." << endl;
		hp += 5;				 // 원하는 만큼 체력 회복량 설정
	}
}

// 지도와 사용자 위치 출력하는 함수
void displayMap(int map[][mapX], int user_x, int user_y)
{
	for (int i = 0; i < mapY; i++)
	{
		for (int j = 0; j < mapX; j++)
		{
			if (i == user_y && j == user_x)
			{
				cout << " USER |";
			}
			else
			{
				int posState = map[i][j];
				switch (posState)
				{
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

// 이동하려는 곳이 유효한 좌표인지 체크하는 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY)
{
	bool checkFlag = false;
	if (user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY)
	{
		checkFlag = true;
	}
	return checkFlag;
}

// 유저의 위치가 목적지인지 체크하는 함수
bool checkGoal(int map[][mapX], int user_x, int user_y)
{
	// 목적지 도착하면
	if (map[user_y][user_x] == 4)
	{
		return true;
	}
	return false;
}