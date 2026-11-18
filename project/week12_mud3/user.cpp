#include "user.h"

User::User() {
    hp = 20;
    itemCnt = 0;
}

void User::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

void User::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
    if (hp < 0) {
        hp = 0;
    }
}

int User::GetHP() const {
    return hp;
}

void User::IncreaseItemCnt() {
    itemCnt++;
}

void User::doAttack() {
    cout << "공격합니다" << endl;
}

ostream& operator<<(ostream& os, const User& user) {
    os << "현재 HP는 " << user.GetHP() << " 이고, 먹은 아이템은 총 " << user.itemCnt << "개 입니다";
    return os;
}

// Magician 재정의
void Magician::doAttack() {
    cout << "마법 사용" << endl;
}

// Warrior 재정의
void Warrior::doAttack() {
    cout << "베기 사용" << endl;
}