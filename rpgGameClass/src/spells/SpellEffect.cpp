#include "../../include/rpg/spells/SpellEffect.h"
#include "../../include/rpg/entities/Character.h"

namespace rpg {

SpellEffect::SpellEffect(const std::string& name, Kind kind, Type type, int manaCost, int power, int range)
    : name(name), kind(kind), type(type), manaCost(manaCost), power(power), range(range) {}

const std::string& SpellEffect::getName() const { return name; }
SpellEffect::Kind SpellEffect::getKind() const { return kind; }
SpellEffect::Type SpellEffect::getType() const { return type; }
int SpellEffect::getManaCost() const { return manaCost; }
int SpellEffect::getPower() const { return power; }
int SpellEffect::getRange() const { return range; }

void SpellEffect::apply(Character& target) const {
    if (kind == Kind::Damage) {
        target.damageHP(power);
    } else if (kind == Kind::Heal) {
        target.healHP(power);
    }
}

} // namespace rpg
