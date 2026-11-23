#pragma once
#include <iostream>
#include <string>
using namespace std;

// 1. User를 인터페이스로 변경
class User {
public:
    virtual ~User() {} // 다형성 소멸을 위한 가상 소멸자
    virtual void DecreaseHP(int dec_hp) = 0;
    virtual void IncreaseHP(int inc_hp) = 0;
    virtual int GetHP() const = 0;
    virtual void DoAttack() const = 0;
};

// User 인터페이스를 구현하는 Magician 클래스
class Magician : public User {
private:
    int hp;
public:
    Magician(int init_hp = 20);
    void DecreaseHP(int dec_hp) override;
    void IncreaseHP(int inc_hp) override;
    int GetHP() const override;
    void DoAttack() const override;
};

// User 인터페이스를 구현하는 Warrior 클래스
class Warrior : public User {
private:
    int hp;
public:
    Warrior(int init_hp = 20);
    void DecreaseHP(int dec_hp) override;
    void IncreaseHP(int inc_hp) override;
    int GetHP() const override;
    void DoAttack() const override;
};