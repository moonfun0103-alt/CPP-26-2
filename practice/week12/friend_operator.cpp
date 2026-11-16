#include <iostream>
using namespace std;

class MyVector
{
private:
    double x, y;
public:
    MyVector(double xvalue = 0.0, double yvalue = 0.0) : x(xvalue), y(yvalue) { }

    // 뺄셈 연산자 (-) 오버로딩: (x1 - x2, y1 - y2)를 담은 새 MyVector 반환
    MyVector operator-(const MyVector& v2) const {
        MyVector v;
        v.x = this->x - v2.x;
        v.y = this->y - v2.y;
        return v;
    }

    friend ostream& operator<<(ostream& os, const MyVector& v) {
        os << "(" << v.x << "," << v.y << ")" << endl;
        return os;
    }

    // 입력 연산자 >> 오버로딩 (값을 수정해야 하므로 const 제거)
    friend istream& operator>>(istream& is, MyVector& v) {
        is >> v.x >> v.y;
        return is;
    }
};

int main()
{
    MyVector v1(1.0, 2.0), v2(3.0, 4.0), v3;
    
    cout << "v3의 x, y 좌표 입력: ";
    cin >> v3;
    
    cout << v1 << v2 << v3;

    // 뺄셈 연산자 테스트
    MyVector v4 = v2 - v1;
    cout << "v2 - v1 = " << v4;
    cout << "v1 - v3 = " << (v1 - v3); // 임시 객체도 const MyVector& 덕분에 바로 출력 가능

    return 0;
}