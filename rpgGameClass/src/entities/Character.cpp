#include "../../include/rpg/entities/Character.h"

namespace rpg {

Character::Character(const std::string& name, int level, int maxHp, int startX, int startY)
        : name(name), lvl(level), maxHP(maxHp), hp(maxHp), speed(10), position{startX, startY} {}
Character::~Character() = default;

const std::string& Character::getName() const {
	return name;
}

int Character::getLvL() const {
	return lvl;
}

int Character::getMaxHp() const {
	return maxHP;
} 

int Character::getHp() const {
	return hp;
}

int Character::getSpeed() const {
        return speed;
}

void Character::setSpeed(int value) {
        speed = value;
}

void Character::damageHP(int value) {
	if(value < 0){
		return;
	}

	hp -= value;
	if(hp<0){
		hp = 0;
	}
}

void Character::healHP(int value) {

	if(value < 0){
		return;
	}

	hp += value;
	if(hp>maxHP){
		hp = maxHP;
	}
}

void Character::setPosition(int x, int y) {
	position[0] = x;
	position[1] = y;
}

std::pair<int, int> Character::getPosition() const {
	return {position[0], position[1]};
}

bool Character::move(int x, int y){
	position[0] += x;
	position[1] += y;
	return true;

}
}  // namespace rpg
