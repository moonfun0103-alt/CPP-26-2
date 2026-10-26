#include <iostream>
using namespace std;

class Time {
private:
    int hour;       // 0-23
    int minute;     // 0-59
public:
    Time(int h, int m);
    void IncHour();
    void Print();

    int GetHour() { return hour; }
    int GetMinute() { return minute; }
    void SetHour(int h) { hour = h; }
    void SetMinute(int m) { minute = m; }
};

Time::Time(int h, int m) { // 외부작성
    hour = h;
    minute = m;
}

void Time::IncHour() { // 외부작성
    ++hour;
    if (hour > 23)
        hour = 0;
}

void Time::Print() { // 외부작성
    cout << hour << ":" << minute << endl;
}

int main()
{
    Time a{ 0, 0 };
    
    // [에러 원인 주석] hour는 private 멤버이므로 main 함수 등 외부에서 직접 접근(수정)할 수 없습니다.
    // 따라서 a.hour = 10; 대신 퍼블릭 멤버 함수인 a.SetHour(10);을 사용해야 에러가 나지 않습니다.
    a.SetHour(10); // 수정: 직접 대입 대신 SetHour 함수 사용
    
    a.SetHour(6);
    a.SetMinute(30);

    a.Print();
    return 0;
}