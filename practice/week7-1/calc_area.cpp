#include <iostream> // 입출력을 위한 헤더 파일을 포함합니다[cite: 4].
using namespace std; // std 네임스페이스를 사용하여 std::를 생략할 수 있게 합니다[cite: 4].

// Circle 클래스를 선언합니다[cite: 4].
class Circle {
public:
    // 멤버 함수의 원형(Prototype)만 클래스 내부에서 선언합니다[cite: 4].
    double calcArea(); 
    
    int radius;     // 반지름을 저장하는 변수입니다[cite: 4].
    string color;   // 색상을 저장하는 변수입니다 (주의: string을 사용하려면 원래 #include <string>이 필요합니다)[cite: 4].
};

// 클래스 외부에서 멤버 함수들이 정의된다[cite: 4].
// 범위 지정 연산자(::)를 사용하여 calcArea() 함수가 Circle 클래스의 멤버 함수임을 명시합니다[cite: 4].
double Circle::calcArea() {
    return 3.14*radius*radius; // 원의 면적을 계산하여 반환합니다[cite: 4].
}

int main()
{
    // Circle 클래스 타입의 객체 c를 생성합니다[cite: 4].
    Circle c; 
    
    // 객체 c의 반지름(radius) 변수에 접근하여 10을 대입합니다[cite: 4].
    c.radius = 10; 
    
    // c.calcArea() 메서드를 호출하여 반환된 결과(3.14 * 10 * 10 = 314)를 화면에 출력합니다[cite: 4].
    cout << c.calcArea() << endl; 
    
    // 프로그램이 정상적으로 실행되었음을 알리고 종료합니다[cite: 4].
    return 0; 
}