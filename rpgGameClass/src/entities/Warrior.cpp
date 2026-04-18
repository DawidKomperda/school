#include "../../include/rpg/entities/Warrior.h"

namespace rpg{

    Warrior::Warrior(const std::string& name, int level, int maxHp, int startX, int startY)
    : Character(name, level, maxHp, startX, startY),
    maxStamina(100), stamina(100), block(0) {
        setSpeed(8);
}

    int Warrior::getMaxStamina() const {
        return maxStamina;
    }

    int Warrior::getStamina() const {
        return stamina;
    }

    int Warrior::getBlock() const {
        return block;
    }

    int Warrior::reduceStamina() {
        constexpr int kDefaultCost = 10;
        if (stamina < kDefaultCost) {
            stamina = 0;
            return stamina;
        }

        stamina -= kDefaultCost;
        return stamina;
    }

    int Warrior::regenStamina() {
        constexpr int kDefaultRegen = 10;
        stamina += kDefaultRegen;
        if (stamina > maxStamina) {
            stamina = maxStamina;
        }

        return stamina;
    }
}