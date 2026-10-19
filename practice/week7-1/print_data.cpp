#include <iostream> // 입출력을 위한 헤더 파일을 포함합니다[cite: 3].
#include <string>   // 문자열(string)을 사용하기 위한 헤더 파일을 포함합니다[cite: 3].
using namespace std; // std::를 생략하기 위해 네임스페이스를 설정합니다[cite: 3].

// 데이터를 출력하는 기능을 가진 PrintData 클래스를 정의합니다[cite: 3].
class PrintData {
public:
    // 아래 3개의 함수는 '함수 오버로딩(Function Overloading)'을 보여줍니다.
    // 같은 이름(print)의 함수지만, 매개변수의 타입이나 개수가 다르면 여러 개 정의할 수 있습니다.

    // 정수(int)형 데이터를 매개변수로 받아 출력하는 메서드입니다[cite: 3].
    void print(int i) { cout << i << endl; }
    
    // 실수(double)형 데이터를 매개변수로 받아 출력하는 메서드입니다[cite: 3].
    void print(double f) { cout << f << endl; }
    
    // 문자열(string) 데이터를 매개변수로 받아 출력하는 메서드입니다[cite: 3].
    // s = "No Data!" 부분은 '디폴트 매개변수(Default Parameter)'로, 인자 없이 호출될 경우 기본으로 "No Data!"를 사용합니다[cite: 3].
    void print(string s = "No Data!") { cout << s << endl; }
};

int main() {
    // PrintData 클래스 타입의 객체(인스턴스)인 obj를 생성합니다[cite: 3].
    PrintData obj;

    // 정수 1을 전달하므로 print(int i)가 호출되어 '1'이 출력됩니다[cite: 3].
    obj.print(1);
    
    // 실수 3.14를 전달하므로 print(double f)가 호출되어 '3.14'가 출력됩니다[cite: 3].
    obj.print(3.14);
    
    // 문자열을 전달하므로 print(string s)가 호출되어 'C++14 is cool.'이 출력됩니다[cite: 3].
    obj.print("C++14 is cool.");
    
    // 아무런 인자를 전달하지 않았으므로, 디폴트 매개변수가 설정된 print(string s)가 호출되어 'No Data!'가 출력됩니다[cite: 3].
    obj.print();
    
    // 프로그램이 정상적으로 실행되었음을 알리고 종료합니다[cite: 3].
    return 0;
}