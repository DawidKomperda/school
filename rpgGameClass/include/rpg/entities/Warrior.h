#pragma once

#include <string>

#include "Character.h"

namespace rpg
{

    class Warrior : public Character
    {

    private:
        int maxStamina;
        int stamina;
        int block;
    public: 
        Warrior(const std::string& name, int level, int maxHp, int startX = 0, int startY = 0);
        int getMaxStamina() const;
        int getStamina() const;
        int getBlock() const;
        int reduceStamina();
        int regenStamina();
    };

}
