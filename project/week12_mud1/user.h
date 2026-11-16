#ifndef USER_H
#define USER_H

class User {
private:
    int hp;

public:
    User();                          // hp = 20으로 설정하며 생성하는 생성자
    void IncreaseHP(int inc_hp);     // HP 증가하는 멤버함수
    void DecreaseHP(int dec_hp);     // HP 감소하는 멤버함수
    int GetHP();                     // HP를 반환하는 멤버함수
};

#endif