#include "../../include/rpg/core/Arena.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <raylib.h>

namespace rpg {

constexpr int TILE_SIZE = 20;
constexpr int UI_HEIGHT = 150;

Arena::Arena(int width, int height, Warrior& warrior, Mage& mage)
        : width(width), height(height), warrior(warrior), mage(mage), selectedCharacter(nullptr), mageDirection(1) {
                mage.addSpell(SpellEffect("Fireball", SpellEffect::Kind::Damage, SpellEffect::Type::Square, 10, 8, 3));
                mage.addSpell(SpellEffect("Heal", SpellEffect::Kind::Heal, SpellEffect::Type::Target, 20, 15, 1));
                mage.addSpell(SpellEffect("Freeze", SpellEffect::Kind::Damage, SpellEffect::Type::Line, 15, 5, 10));
}

void Arena::render() const {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw grid
        for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                        DrawRectangleLines(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, LIGHTGRAY);
                }
        }

        // Target coordinates
        const auto [wx, wy] = warrior.getPosition();
        const auto [mx, my] = mage.getPosition();

        // Draw selection range
        if (selectedCharacter) {
                const auto [sx, sy] = selectedCharacter->getPosition();
                DrawCircleLines(sx * TILE_SIZE + TILE_SIZE / 2, sy * TILE_SIZE + TILE_SIZE / 2, selectedCharacter->getSpeed() * TILE_SIZE, GREEN);
        }

        // Draw warrior
        if (wx >= 0 && wx < width && wy >= 0 && wy < height) {
                DrawRectangle(wx * TILE_SIZE, wy * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLUE);
                DrawText("W", wx * TILE_SIZE + 4, wy * TILE_SIZE + 2, 10, WHITE);
        }

        // Draw mage
        if (mx >= 0 && mx < width && my >= 0 && my < height) {
                DrawRectangle(mx * TILE_SIZE, my * TILE_SIZE, TILE_SIZE, TILE_SIZE, PURPLE);
                DrawText("M", mx * TILE_SIZE + 4, my * TILE_SIZE + 2, 10, WHITE);
        }

        // Draw UI
        int uiStartY = height * TILE_SIZE + 10;
        DrawText("=== Characters ===", 10, uiStartY, 20, DARKGRAY);
        DrawText(TextFormat("Warrior (HP: %d)", warrior.getHp()), 10, uiStartY + 30, 20, BLUE);
        DrawText(TextFormat("Mage (HP: %d, Mana: %d)", mage.getHp(), mage.getMana()), 10, uiStartY + 60, 20, PURPLE);
        
        DrawText("Spells:", 250, uiStartY + 30, 20, DARKGRAY);
        int i = 0;
        for (const auto& spell : mage.getSpells()) {
                DrawText(TextFormat("- %s (Mana: %d)", spell.getName().c_str(), spell.getManaCost()), 250, uiStartY + 60 + (i * 20), 20, DARKGRAY);
                i++;
        }

        EndDrawing();
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
        InitWindow(width * TILE_SIZE, height * TILE_SIZE + UI_HEIGHT, "RPG Arena");
        SetTargetFPS(60);

        int remainingTicks = ticks;
        double lastUpdateTime = GetTime();

        while (!WindowShouldClose() && remainingTicks != 0) {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        int mouseGridX = GetMouseX() / TILE_SIZE;
                        int mouseGridY = GetMouseY() / TILE_SIZE;
                        
                        const auto [wx, wy] = warrior.getPosition();
                        const auto [mx, my] = mage.getPosition();
                        
                        if (mouseGridX == wx && mouseGridY == wy) {
                                selectedCharacter = &warrior;
                        } else if (mouseGridX == mx && mouseGridY == my) {
                                selectedCharacter = &mage;
                        } else {
                                if (selectedCharacter) {
                                        float dx = static_cast<float>(mouseGridX) - selectedCharacter->getPosition().first;
                                        float dy = static_cast<float>(mouseGridY) - selectedCharacter->getPosition().second;
                                        float distance = std::sqrt(dx * dx + dy * dy);
                                        
                                        if (distance <= selectedCharacter->getSpeed()) {
                                                selectedCharacter->setPosition(mouseGridX, mouseGridY);
                                                selectedCharacter = nullptr;
                                        } else {
                                                selectedCharacter = nullptr;
                                        }
                                } else {
                                        selectedCharacter = nullptr;
                                }
                        }
                }

                double currentTime = GetTime();
                
                // Update logic every 1 second
                if (currentTime - lastUpdateTime >= 1.0) {

                        if (remainingTicks > 0) {
                                --remainingTicks;
                        }
                }

                render();
        }

        CloseWindow();
}

}  // namespace rpg
