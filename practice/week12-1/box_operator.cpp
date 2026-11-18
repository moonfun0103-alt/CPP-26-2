#include <iostream>
using namespace std;

class Box
{
private:
    double length, width, height;

public:
    Box(double l = 0.0, double w = 0.0, double h = 0.0) 
        : length(l), width(w), height(h) { }

    // 두 상자의 가로, 세로, 높이가 모두 같은지 비교
    bool operator==(const Box& b2) const {
        return (length == b2.length &&
                width == b2.width &&
                height == b2.height);
    }

    // == 연산자를 재사용하여 다른지 비교
    bool operator!=(const Box& b2) const {
        return !(*this == b2);
    }

    // 앞서 보신 << 연산자 오버로딩도 함께 적용 (상자 정보 출력)
    friend ostream& operator<<(ostream& os, const Box& b) {
        os << "(" << b.length << ", " << b.width << ", " << b.height << ")";
        return os;
    }
};

int main()
{
    Box b1(10.0, 20.0, 30.0), b2(10.0, 20.0, 30.0), b3(5.0, 5.0, 5.0);

    cout << "b1: " << b1 << endl;
    cout << "b2: " << b2 << endl;
    cout << "b3: " << b3 << endl;

    // 참과 거짓을 1, 0이 아니라 true, false로 출력하도록 설정
    cout.setf(cout.boolalpha);
    cout << "b1 == b2 : " << (b1 == b2) << endl;
    cout << "b1 != b2 : " << (b1 != b2) << endl;
    cout << "b1 == b3 : " << (b1 == b3) << endl;

    return 0;
}