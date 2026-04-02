#pragma once

#include "../entities/Mage.h"
#include "../entities/Warrior.h"

namespace rpg {

class Arena {
   private:
	int width;
	int height;
	Warrior& warrior;
	Mage& mage;
	int mageDirection;

	void updateDemoPositions();

   public:
	Arena(int width, int height, Warrior& warrior, Mage& mage);
	void render() const;
	void run(int ticks = -1);
};

}  // namespace rpg
