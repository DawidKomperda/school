#pragma once

#include <string>

#include "Character.h"

namespace rpg
{

    class Mage : public Character
    {
    private:
        int maxMana;
        int mana;

    public:
        Mage(const std::string &name, int level, int maxHp, int maxMana, int startX = 0, int startY = 0);

        int getMaxMana() const;
        int getMana() const;
        // Spell consumes 10 mana
        void castSpell();
    };

} // namespace rpg
