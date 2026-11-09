#include <iostream>
#include <string>

using namespace std;

class Date {
    int year, month, day;
public:
    Date(int y, int m, int d) { year = y; month = m; day = d; }
    void Print() {
        cout << year << "." << month << "." << day << endl;
    }
};

class Person {
    string name;
    Date birth;
public:
    // 이전 에러를 완벽하게 해결하는 초기화 리스트 방식
    Person(string n, Date d) : name(n), birth(d) {}
    
    void Print() {
        cout << name << ":";
        birth.Print();
    }
};

int main()
{
    // 버전 충돌을 막기 위해 {} 대신 () 사용
    Date d(1998, 3, 1);
    Person p("김철수", d);
    
    p.Print(); 
    return 0;
}