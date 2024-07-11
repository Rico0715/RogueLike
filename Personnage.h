#pragma once
#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Sort.h"
#include <vector>
#include "Projectile.h"
#include "Monstre.h"
class Spell;

class Personnage {
private:
    std::string name;
    int healthPoints;
    int maxHealthPoints; // Ajouter un membre pour les points de vie maximum
    int attackDamage;
    int armorPoints;
    int mana;
    int level;
    bool alive;
    float attackSpeed; // New attribute for attack speed
    std::vector<Spell> spells; // Collection of spells

    // SFML attributes
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<sf::IntRect> frames; // Rectangles for each frame of the sprite sheet
    size_t currentFrame;


    // Shooting attributes
    sf::Clock shootClock;
    // Removed shootInterval constant

public:
    // Constructors
    Personnage();
    Personnage(std::string n, int hp, int ad, int ar, int mana, int lvl, float attackSpeed, std::vector<Spell> s, const std::string& textureFile);

    // Methods
    void displayCharacter() const;
    void autoAttack(Personnage& target) const;
    void castSpell(int index, Personnage& target);
    void receiveDamage(int damage);
    void shoot(std::vector<Projectile>& projectiles, const std::string& projectileTextureFile, const sf::RenderWindow& window);
    bool isAlive() const;
    void resetHealth(); // Nouvelle méthode pour réinitialiser les points de vie

    // Accessors and Mutators
    std::string getName() const;
    int getHealthPoints() const;
    int getMana() const;
    float getAttackSpeed() const; // Getter for attack speed
    void setAttackSpeed(float speed); // Setter for attack speed
    int getMaxHealthPoints() const;
    float getHealthPercentage() const;

    // SFML Methods
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    void setFrame(size_t frameIndex);
    void move(float offsetX, float offsetY, const sf::RenderWindow& window); // New method
    void handleInput(const sf::RenderWindow& window);
    bool canShoot(); // New method to check if character can shoot
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;  // New method to get the bounding box


};

#endif // PERSONNAGE_H
