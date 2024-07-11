#pragma once

#include <string>
#include "Personnage.h" // Include to access Personnage

class Personnage;
class Spell {
private:
    std::string name;
    int damage;
    int manaCost;

public:
    Spell(std::string n, int d, int mana);
    void castSpell(Personnage &target) const;
    std::string getName() const;
    int getDamage() const;
    int getManaCost() const;
};
