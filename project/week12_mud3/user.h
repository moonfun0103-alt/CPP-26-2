#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class User {
private:
    int hp;
    int itemCnt;

public:
    User();
    void IncreaseHP(int inc_hp);
    void DecreaseHP(int dec_hp);
    int GetHP() const;
    void IncreaseItemCnt();

    // User 클래스 확장: 공격 함수 추가
    virtual void doAttack();

    // 출력(<<) 연산자 중복 정의
    friend ostream& operator<<(ostream& os, const User& user);
};

// User 클래스를 상속받는 Magician 클래스
class Magician : public User {
public:
    void doAttack() override; // "마법 사용" 출력으로 재정의
};

// User 클래스를 상속받는 Warrior 클래스
class Warrior : public User {
public:
    void doAttack() override; // "베기 사용" 출력으로 재정의
};

#endif