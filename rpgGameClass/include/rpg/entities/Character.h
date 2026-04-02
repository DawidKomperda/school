#pragma once
#include <string>
#include <utility>
namespace rpg {

class Character {
    private: 
        std::string name;
        int lvl;
        int maxHP;
        int hp;
        int position[2];

    public:
        Character(const std::string& name, int level, int maxHp, int startX = 0, int startY = 0);
        virtual ~Character();

        const std::string& getName() const;
        int getLvL() const;
        int getMaxHp() const;
        int getHp() const;
        void damageHP(int value);
        void healHP(int value);
        void setPosition(int x, int y);
        std::pair<int, int> getPosition() const;
        bool move(int x, int y);
    };
   
}