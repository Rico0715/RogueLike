#include "Sort.h"
#include "Personnage.h" // Include to access Personnage methods if needed
#include <iostream>

// Constructor
Spell::Spell(std::string n, int d, int mana) : name(n), damage(d), manaCost(mana) {}

// Method to cast the spell
void Spell::castSpell(Personnage &target) const {
    // Reduce the target's health points by the spell's damage
    target.receiveDamage(damage);
    std::cout << name << " cast, dealing " << damage << " damage." << std::endl;
}

// Accessors
std::string Spell::getName() const {
    return name;
}

int Spell::getDamage() const {
    return damage;
}

int Spell::getManaCost() const {
    return manaCost;
}