#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s1 = "사과";
    string s2;
    // 에러 이유: C++에서 문자열 리터럴("")과 문자열 객체(string)끼리의 덧셈은 가능하지만, 
    // 정수(10)를 직접 더하려고 하면 string과 더할 수 있는 연산자(operator+)가 없어 컴파일 에러가 발생합니다.
    // 해결하려면 to_string(10)과 같이 문자열로 변환한 뒤 더해야 합니다.
    s2 = s1 + " " + to_string(10) + "개";
    cout << s2 << endl;
}