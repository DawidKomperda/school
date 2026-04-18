#include "../../include/rpg/entities/Mage.h"

namespace rpg {
Mage::Mage(const std::string& name, int level, int maxHp, int maxMana, int startX, int startY)
        : Character(name, level, maxHp, startX, startY), maxMana(maxMana), mana(maxMana) {
        setSpeed(5);
}


int Mage::getMaxMana() const {
        return maxMana;
}

int Mage::getMana() const {
        return mana;
}

void Mage::addSpell(const SpellEffect& spell) {
        spellbook.push_back(spell);
}

const std::vector<SpellEffect>& Mage::getSpells() const {
        return spellbook;
}

bool Mage::castSpell(Character& target, const SpellEffect& spell) {
        if (spell.getManaCost() < 0) {
                return false;
        }

        if (mana < spell.getManaCost()) {
                return false;
        }

        mana -= spell.getManaCost();
        spell.apply(target);
        return true;
}

}  // namespace rpg
