#include "../../include/rpg/entities/Mage.h"

namespace rpg {
Mage::Mage(const std::string& name, int level, int maxHp, int maxMana, int startX, int startY)
	: Character(name, level, maxHp, startX, startY), mana(maxMana), maxMana(maxMana) {}


int Mage::getMaxMana() const {
	return maxMana;
}

int Mage::getMana() const {
	return mana;
}

void Mage::castSpell() {
	constexpr int kDefaultSpellCost = 10;
	if (mana < kDefaultSpellCost) {
		return;
	}

	mana -= kDefaultSpellCost;
}

}  // namespace rpg