// complex_add.cpp
#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;
    Complex(double r = 0.0, double i = 0.0) {
        real = r;
        imag = i;
        cout << "생성자 호출" << endl;
        Print();
    }
    ~Complex() {
        cout << "소멸자 호출" << endl;
        Print();
    }
    void Print() {
        cout << real << "+" << imag << "i" << endl;
    }
};

// 두 복소수를 더하는 Add 함수 추가
Complex Add(Complex c1, Complex c2) {
    Complex temp;
    temp.real = c1.real + c2.real;
    temp.imag = c1.imag + c2.imag;
    return temp;
}

int main()
{
    Complex c1{ 1, 2 }, c2{ 3, 4 };
    Complex t;
    
    // 이제 Add 함수를 정상적으로 사용할 수 있습니다.
    t = Add(c1, c2); 
    t.Print();
    
    return 0;
}