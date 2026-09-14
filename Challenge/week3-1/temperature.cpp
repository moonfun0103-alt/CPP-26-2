#include <iostream>
using namespace std;

int main()
{
    double fahrenheit;

    cout << "화씨온도 입력: ";
    cin >> fahrenheit;

    double celsius = (5.0 / 9.0) * (fahrenheit - 32);

    cout << "화씨온도: " << fahrenheit << endl;
    cout << "섭씨온도 = " << celsius << endl;

    return 0;
}