#include "user.h"

User::User() {
    hp = 20;
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

int User::GetHP() {
    return hp;
}