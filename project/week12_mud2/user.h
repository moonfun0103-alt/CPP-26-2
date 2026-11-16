#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class User {
private:
    int hp;
    int itemCnt; // 아이템 먹은 횟수를 저장하는 변수

public:
    User();                          // hp = 20, itemCnt = 0 초기화
    void IncreaseHP(int inc_hp);     // HP 증가
    void DecreaseHP(int dec_hp);     // HP 감소
    int GetHP() const;               // HP 반환 (const 객체에서도 호출 가능하도록 const 지정)
    void IncreaseItemCnt();          // 아이템 먹은 횟수 1 증가

    // 출력(<<) 연산자 중복 정의
    friend ostream& operator<<(ostream& os, const User& user);
};

#endif