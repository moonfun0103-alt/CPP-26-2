#include <iostream>
using namespace std;

int main()
{
    int money, price;

    cout << "가지고 있는 돈 입력: ";
    cin >> money;
    cout << "캔디의 가격 입력: ";
    cin >> price;

    int max_candy = money / price;
    int remaining_money = money % price;

    cout << "현재 가지고 있는 돈: " << money << endl;
    cout << "캔디의 가격 : " << price << endl;
    cout << "최대로 살 수 있는 캔디 = " << max_candy << endl;
    cout << "캔디 구입 후 남은 돈 = " << remaining_money << endl;

    return 0;
}