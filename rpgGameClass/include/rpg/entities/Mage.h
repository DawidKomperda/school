#pragma once

#include <string>
#include <vector>

#include "Character.h"
#include "../spells/SpellEffect.h"

namespace rpg
{

    class Mage : public Character
    {
    private:
        int maxMana;
        int mana;
        std::vector<SpellEffect> spellbook;

    public:
        Mage(const std::string &name, int level, int maxHp, int maxMana, int startX = 0, int startY = 0);

        int getMaxMana() const;
        int getMana() const;
        
        void addSpell(const SpellEffect& spell);
        const std::vector<SpellEffect>& getSpells() const;

        // Spell consumes mana
		bool castSpell(Character& target, const SpellEffect& spell);
    };

} // namespace rpg
