// ASCII 기반 자율주행 경로 탐색 및 회피 제어 시뮬레이터
// 진척 보고서 #1 시점 구현 범위: 기능 1-1, 1-2, 2-1
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

const char ROAD = '.';
const char WALL = '#';
const char OBST = 'O';
const char CAR  = 'C';
const char GOAL = 'G';

// 상, 하, 좌, 우 이동량
const int DR[4] = {-1, 1, 0, 0};
const int DC[4] = {0, 0, -1, 1};
const char DIR_NAME[4] = {'U', 'D', 'L', 'R'};

const int DELAY_MS = 150;   // 한 턴 간격
const int MAX_TURN = 300;   // 최대 턴 수

struct Point {
    int r, c;
};

class Map {
private:
    int rows, cols;
    vector<vector<char>> grid;   // 2차원 배열 맵
    vector<Point> obstacles;     // 동적 장애물 위치 목록
    Point car, goal;

public:
    Map(int r, int c);
    void placeObstacles(int count);
    void moveObstacles();
    int heuristic(Point from, Point to) const;
    int chooseDirection(int* costs) const;
    void moveCar(int dir);
    void render(int turn, const int* costs, int dir) const;
    bool arrived() const { return car.r == goal.r && car.c == goal.c; }
};

// [기능 1-1] 맵 설정: 테두리는 벽, 내부는 도로로 초기화
Map::Map(int r, int c) : rows(r), cols(c), grid(r, vector<char>(c, ROAD)) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
                grid[i][j] = WALL;
        }
    }
    car = {1, 1};                      // 출발지: 좌상단
    goal = {rows - 2, cols - 2};       // 목적지: 우하단
    grid[car.r][car.c] = CAR;
    grid[goal.r][goal.c] = GOAL;
}

// [기능 1-1] 동적 장애물을 빈 도로 칸에 무작위로 배치
void Map::placeObstacles(int count) {
    int placed = 0;
    while (placed < count) {
        int r = rand() % (rows - 2) + 1;
        int c = rand() % (cols - 2) + 1;
        if (grid[r][c] != ROAD) continue;   // 벽, 차량, 목적지, 다른 장애물 칸 제외
        if (r <= 2 && c <= 2) continue;     // 출발지 주변은 비워 둠
        grid[r][c] = OBST;
        obstacles.push_back({r, c});
        placed++;
    }
}

// [기능 1-1] 매 턴 장애물을 상하좌우 중 한 칸 무작위 이동
void Map::moveObstacles() {
    for (Point& ob : obstacles) {
        int d = rand() % 4;
        int nr = ob.r + DR[d];
        int nc = ob.c + DC[d];
        if (grid[nr][nc] != ROAD) continue; // 막혀 있으면 제자리
        grid[ob.r][ob.c] = ROAD;
        grid[nr][nc] = OBST;
        ob = {nr, nc};
    }
}

// [기능 2-1] 휴리스틱 비용: 목적지까지의 맨해튼 거리
int Map::heuristic(Point from, Point to) const {
    return abs(from.r - to.r) + abs(from.c - to.c);
}

// [기능 2-1] 인접 4칸의 비용을 계산해 가장 작은 방향을 반환 (갈 곳이 없으면 -1)
int Map::chooseDirection(int* costs) const {
    int best = -1;
    for (int d = 0; d < 4; d++) {
        Point next = {car.r + DR[d], car.c + DC[d]};
        char cell = grid[next.r][next.c];
        if (cell != ROAD && cell != GOAL) { // 벽이나 장애물은 이동 불가
            costs[d] = -1;
            continue;
        }
        costs[d] = heuristic(next, goal);
        if (best == -1 || costs[d] < costs[best]) best = d;
    }
    return best;
}

void Map::moveCar(int dir) {
    if (dir == -1) return;                  // 사방이 막히면 대기
    grid[car.r][car.c] = ROAD;
    car = {car.r + DR[dir], car.c + DC[dir]};
    grid[car.r][car.c] = CAR;
}

// [기능 1-2] 화면을 지우지 않고 커서만 좌상단으로 옮겨 덮어쓰기 (깜빡임 방지)
void Map::render(int turn, const int* costs, int dir) const {
    string buf = "\033[H";                  // 커서를 화면 좌상단으로 이동
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char ch = grid[i][j];
            if (ch == CAR)       buf += "\033[92m";  // 초록
            else if (ch == GOAL) buf += "\033[93m";  // 노랑
            else if (ch == OBST) buf += "\033[91m";  // 빨강
            else if (ch == WALL) buf += "\033[90m";  // 회색
            buf += ch;
            buf += "\033[0m ";
        }
        buf += "\033[K\n";                  // 줄 끝에 남은 이전 출력 제거
    }
    buf += "Turn " + to_string(turn);
    buf += " | Car (" + to_string(car.r) + "," + to_string(car.c) + ")";
    buf += " | Goal (" + to_string(goal.r) + "," + to_string(goal.c) + ")\033[K\n";
    buf += "Cost ";
    for (int d = 0; d < 4; d++) {
        buf += DIR_NAME[d];
        buf += ':';
        buf += (costs[d] < 0 ? string("--") : to_string(costs[d]));
        buf += ' ';
    }
    buf += "-> ";
    buf += (dir == -1 ? '-' : DIR_NAME[dir]);
    buf += "\033[K\n";
    cout << buf << flush;                   // 한 프레임을 한 번에 출력
}

int main() {
    int rows = 0, cols = 0, count = 0;
    cout << "Map rows (5-20): ";
    cin >> rows;
    cout << "Map cols (5-40): ";
    cin >> cols;
    cout << "Obstacles: ";
    cin >> count;
    if (rows < 5 || rows > 20 || cols < 5 || cols > 40 ||
        count < 0 || count > (rows - 2) * (cols - 2) / 4) {
        cout << "Invalid input." << endl;
        return 1;
    }

    srand((unsigned)time(nullptr));
    Map map(rows, cols);
    map.placeObstacles(count);

    int costs[4] = {-1, -1, -1, -1};
    int turn = 0;
    cout << "\033[2J\033[?25l";             // 시작할 때 한 번만 화면을 지우고 커서 숨김
    map.render(turn, costs, -1);

    while (!map.arrived() && turn < MAX_TURN) {
        this_thread::sleep_for(chrono::milliseconds(DELAY_MS));
        turn++;
        map.moveObstacles();                    // 1) 장애물 이동
        int dir = map.chooseDirection(costs);   // 2) 비용 계산 및 방향 결정
        map.moveCar(dir);                       // 3) 차량 이동
        map.render(turn, costs, dir);           // 4) 화면 갱신
    }

    cout << "\033[?25h";                    // 커서 다시 표시
    if (map.arrived()) cout << "Arrived in " << turn << " turns." << endl;
    else cout << "Stopped: turn limit reached." << endl;
    return 0;
}
