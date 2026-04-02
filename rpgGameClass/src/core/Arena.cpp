#include "../../include/rpg/core/Arena.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace rpg {

Arena::Arena(int width, int height, Warrior& warrior, Mage& mage)
	: width(width), height(height), warrior(warrior), mage(mage), mageDirection(1) {}

void Arena::render() const {
	std::vector<std::string> grid(height, std::string(width, '.'));

	const auto [wx, wy] = warrior.getPosition();
	const auto [mx, my] = mage.getPosition();

	if (wx >= 0 && wx < width && wy >= 0 && wy < height) {
		grid[wy][wx] = 'w';
	}

	if (mx >= 0 && mx < width && my >= 0 && my < height) {
		grid[my][mx] = 'm';
	}

	std::cout << "\x1B[2J\x1B[H";
	std::cout << '+' << std::string((width * 2) + 1, '-') << "+\n";
	for (int y = 0; y < height; ++y) {
		std::cout << "| ";
		for (int x = 0; x < width; ++x) {
			std::cout << grid[y][x] << ' ';
		}
		std::cout << "|\n";
	}
	std::cout << '+' << std::string((width * 2) + 1, '-') << "+\n";

	std::cout << "\n=== Characters ===\n";
	std::cout << "w - " << warrior.getName() << " (HP: " << warrior.getHp() << ")\n";
	std::cout << "m - " << mage.getName() << " (HP: " << mage.getHp() << ")\n";
	std::cout.flush();
}

void Arena::updateDemoPositions() {
	const auto [mx, my] = mage.getPosition();
	int nextX = mx + mageDirection;
	if (nextX <= 0 || nextX >= width - 1) {
		mageDirection *= -1;
		nextX = mx + mageDirection;
	}

	mage.setPosition(nextX, my);
}

void Arena::run(int ticks) {
	int remainingTicks = ticks;
	while (remainingTicks != 0) {
		render();
		updateDemoPositions();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if (remainingTicks > 0) {
			--remainingTicks;
		}
	}
}

}  // namespace rpg
