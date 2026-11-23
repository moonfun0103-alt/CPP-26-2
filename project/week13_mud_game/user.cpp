#include "user.h"

// Magician 구현
Magician::Magician(int init_hp) : hp(init_hp) {}

void Magician::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

void Magician::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

int Magician::GetHP() const {
    return hp;
}

void Magician::DoAttack() const {
    cout << "마법 사용" << endl;
}

// Warrior 구현
Warrior::Warrior(int init_hp) : hp(init_hp) {}

void Warrior::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

void Warrior::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

int Warrior::GetHP() const {
    return hp;
}

void Warrior::DoAttack() const {
    cout << "베기 사용" << endl;
}