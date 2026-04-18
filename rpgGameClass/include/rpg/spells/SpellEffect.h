#pragma once

#include <string>

namespace rpg {

class Character;

class SpellEffect {
   public:
		enum class Kind {
			Damage,
			Heal
		};

		enum class Type {
			Target,
			Square,
			Line
		};

		SpellEffect(const std::string& name, Kind kind, Type type, int manaCost, int power, int range);

		const std::string& getName() const;
		Kind getKind() const;
		Type getType() const;
		int getManaCost() const;
		int getPower() const;
		int getRange() const;

		void apply(Character& target) const;

   private:
		std::string name;
		Kind kind;
		Type type;
		int manaCost;
		int power;
		int range;
};

}  // namespace rpg
