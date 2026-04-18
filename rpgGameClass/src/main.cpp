#include "../include/rpg/core/Arena.h"
#include "../include/rpg/entities/Mage.h"
#include "../include/rpg/entities/Warrior.h"

int main() {
    rpg::Warrior warrior("Warrior", 1, 120, 5, 5);
    rpg::Mage mage("Mage", 1, 90, 200, 30, 30);

    rpg::Arena arena(40, 40, warrior, mage);
    arena.run();

    return 0;
}
