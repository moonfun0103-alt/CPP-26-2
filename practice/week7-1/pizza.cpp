#include <iostream> // 화면 입출력(cout 등)을 위한 헤더 파일 포함
#include <string>   // 문자열(string) 변수를 사용하기 위한 헤더 파일 포함
using namespace std; // std::를 생략하고 편리하게 표준 라이브러리를 사용하기 위함

// 'Circle'이라는 이름의 클래스 정의 (원의 속성과 동작을 정의하는 틀/설계도)
class Circle {
public: // 접근 제어자: 클래스 외부(main 함수 등)에서도 이 아래의 변수와 함수에 접근할 수 있도록 허용함
    int radius;     // 원의 반지름을 저장할 정수형 멤버 변수
    string color;   // 원의 색상을 저장할 문자열 멤버 변수

    // 원의 면적을 계산하여 실수형(double)으로 반환하는 멤버 함수(메서드)
    double CalcArea() {
        return 3.14 * radius * radius; // 원의 넓이 공식 (π * r^2) 계산 후 결과값 반환
    }
};

int main() {
    Circle obj; // Circle 클래스(설계도)를 바탕으로 'obj'라는 이름의 실제 객체(인스턴스)를 생성

    obj.radius = 100;   // 생성된 원 객체(obj)의 반지름(radius) 속성 값에 100을 대입
    obj.color = "blue"; // 생성된 원 객체(obj)의 색상(color) 속성 값에 "blue"를 대입

    // "원의 면적="이라는 텍스트 출력 후, obj 객체의 CalcArea() 함수를 실행하여 계산된 면적(31400)을 출력
    cout << "원의 면적=" << obj.CalcArea() << "\n";
    
    return 0; // 프로그램 정상 종료
}

int main() 
{
    // Circle 클래스 타입의 객체(인스턴스)인 pizza1과 pizza2를 생성합니다[cite: 1].
    Circle pizza1, pizza2; 

    // pizza1 객체의 멤버 변수에 접근하여 반지름(radius)을 100으로, 색상(color)을 "yellow"로 설정합니다[cite: 1].
    pizza1.radius = 100; 
    pizza1.color = "yellow"; 
    
    // pizza1의 CalcArea() 메서드를 호출하여 반환된 피자의 면적 값을 콘솔에 출력합니다[cite: 1].
    cout << "피자의 면적=" << pizza1.CalcArea() << "\n"; 

    // pizza2 객체의 멤버 변수에 접근하여 반지름(radius)을 200으로, 색상(color)을 "white"로 설정합니다[cite: 1].
    pizza2.radius = 200; 
    pizza2.color = "white"; 
    
    // pizza2의 CalcArea() 메서드를 호출하여 반환된 피자의 면적 값을 콘솔에 출력합니다[cite: 1].
    cout << "피자의 면적=" << pizza2.CalcArea() << "\n"; 
    
    // 프로그램이 정상적으로 실행되었음을 알리고 종료합니다[cite: 1].
    return 0; 
}