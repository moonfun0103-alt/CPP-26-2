#include <iostream> // 입출력을 위한 헤더 파일을 포함합니다[cite: 2].
#include <string>   // 문자열(string)을 사용하기 위한 헤더 파일을 포함합니다[cite: 2].
using namespace std; // std 네임스페이스를 사용하여 std:: 생략 가능하게 합니다[cite: 2].

// 자동차의 속성을 정의하는 Car 클래스를 선언합니다[cite: 2].
class Car {
public: // 클래스 외부에서도 접근할 수 있도록 접근 제어자를 public으로 설정합니다[cite: 2].
    // 멤버 변수 선언[cite: 2]
    int speed; // 속도를 저장하는 변수[cite: 2]
    int gear; // 기어 단수를 저장하는 변수[cite: 2]
    string color; // 색상을 저장하는 변수[cite: 2]

    // 멤버 함수 선언[cite: 2]
    void SpeedUp() { // 속도 증가 멤버 함수[cite: 2]
        speed += 10; // 현재 속도에서 10을 증가시킵니다[cite: 2].
    }

    void SpeedDown() { // 속도 감소 멤버 함수[cite: 2]
        speed -= 10; // 현재 속도에서 10을 감소시킵니다[cite: 2].
    }
};

int main()
{
    // Car 클래스 타입의 객체(인스턴스)인 myCar를 생성합니다[cite: 2].
    Car myCar;

    // myCar 객체의 멤버 변수에 초기값을 설정합니다[cite: 2].
    myCar.speed = 100; // 속도를 100으로 설정[cite: 2]
    myCar.gear = 3;    // 기어를 3으로 설정[cite: 2]
    myCar.color = "red"; // 색상을 "red"(빨간색)로 설정[cite: 2]

    // 첫 번째 속도 상태를 출력합니다 (100 출력)[cite: 2].
    cout <<"1st speed: " << myCar.speed << endl;

    // 속도를 올리는 메서드를 호출합니다. speed가 100에서 110으로 증가합니다[cite: 2].
    myCar.SpeedUp();
    // 두 번째 속도 상태를 출력합니다 (110 출력)[cite: 2].
    cout << "2nd speed: " << myCar.speed << endl;

    // 속도를 내리는 메서드를 호출합니다. speed가 110에서 100으로 감소합니다[cite: 2].
    myCar.SpeedDown();
    // 세 번째 속도 상태를 출력합니다 (100 출력)[cite: 2].
    cout << "3rd speed: " << myCar.speed << endl;

    // 프로그램을 정상적으로 종료합니다[cite: 2].
    return 0;
}