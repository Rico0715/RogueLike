#include "Personnage.h"
#include <iostream>
#include <string>
#include <cmath>

// Default constructor
Personnage::Personnage() : name("Garen"), healthPoints(900), attackDamage(60), armorPoints(40), mana(0), level(1), attackSpeed(1.0f) { // Default attack speed
    std::cout << "Default constructor called" << std::endl;
}

// Parameterized constructor
Personnage::Personnage(std::string n, int hp, int ad, int ar, int mana, int lvl, float attackSpeed, std::vector<Spell> s, const std::string& textureFile)
    : name(n), healthPoints(hp), maxHealthPoints(hp), alive(true), attackDamage(ad), armorPoints(ar), mana(mana), level(lvl), attackSpeed(attackSpeed), spells(s), currentFrame(0)
{
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture" << std::endl;
    }
    sprite.setTexture(texture);

    // Assuming each sprite is 32x32 pixels
    int spriteWidth = 32;
    int spriteHeight = 32;
    int textureWidth = texture.getSize().x;
    int textureHeight = texture.getSize().y;

    for (int y = 0; y < textureHeight / spriteHeight; ++y) {
        for (int x = 0; x < textureWidth / spriteWidth; ++x) {
            frames.emplace_back(x * spriteWidth, y * spriteHeight, spriteWidth, spriteHeight);
        }
    }

    // Set the initial frame
    sprite.setTextureRect(frames[currentFrame]);
}

// Method to display character information
void Personnage::displayCharacter() const {
    std::cout << "Name: " << name
        << ", HP: " << healthPoints
        << ", AD: " << attackDamage
        << ", Armor: " << armorPoints
        << ", Mana: " << mana
        << ", Level: " << level
        << ", Attack Speed: " << attackSpeed
        << std::endl;
}

// Method to attack another character
void Personnage::autoAttack(Personnage& target) const {
    int reducedDamage = attackDamage / (1 + (target.armorPoints / 100.0));
    target.healthPoints -= reducedDamage;
    std::cout << this->name << " attacks " << target.name << " dealing " << reducedDamage << " damage." << std::endl;
    std::cout << target.name << " has " << target.healthPoints << " health points remaining." << std::endl;
}

// Method to cast a spell on another character
void Personnage::castSpell(int index, Personnage& target) {
    if (index >= 0 && index < spells.size()) {
        if (mana >= spells[index].getManaCost()) {
            mana -= spells[index].getManaCost();
            spells[index].castSpell(target);
        }
        else {
            std::cout << "Insufficient mana to cast " << spells[index].getName() << std::endl;
        }
    }
    else {
        std::cout << "Invalid spell index" << std::endl;
    }
}

// Method to receive damage
void Personnage::receiveDamage(int damage) {
    healthPoints -= damage;
    if (healthPoints <= 0) {
        healthPoints = 0;
        alive = false; // Mettre le personnage comme mort quand healthPoints <= 0
        std::cout << name << " has been defeated!" << std::endl;
        // Autres actions à prendre lorsque le personnage est vaincu
    }
    else {
        std::cout << name << " now has " << healthPoints << " health points." << std::endl;
    }
}

bool Personnage::isAlive() const {
    return alive;
}


void Personnage::resetHealth() {
    healthPoints = maxHealthPoints; // Remettre à la valeur initiale ou une valeur définie IMPORTANT A CHANGER
    alive = true;
}

// Accessors
std::string Personnage::getName() const {
    return name;
}

int Personnage::getHealthPoints() const {
    return healthPoints;
}

int Personnage::getMana() const {
    return mana;
}

float Personnage::getAttackSpeed() const {
    return attackSpeed;
}

void Personnage::setAttackSpeed(float speed) {
    attackSpeed = speed;
}

int Personnage::getMaxHealthPoints() const
{
    return maxHealthPoints;

}

float Personnage::getHealthPercentage() const
{
    return static_cast<float>(healthPoints) / maxHealthPoints * 100.0f;
}

sf::Vector2f Personnage::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Personnage::getBounds() const
{
    return sprite.getGlobalBounds();
}



// SFML Methods
void Personnage::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Personnage::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Personnage::setFrame(size_t frameIndex) {
    if (frameIndex < frames.size()) {
        currentFrame = frameIndex;
        sprite.setTextureRect(frames[currentFrame]);
    }
}

void Personnage::move(float offsetX, float offsetY, const sf::RenderWindow& window) {
    sf::Vector2f newPosition = sprite.getPosition() + sf::Vector2f(offsetX, offsetY);

    // Check bounds
    if (newPosition.x < 0) newPosition.x = 0;
    if (newPosition.y < 0) newPosition.y = 0;
    if (newPosition.x + sprite.getGlobalBounds().width > window.getSize().x)
        newPosition.x = window.getSize().x - sprite.getGlobalBounds().width;
    if (newPosition.y + sprite.getGlobalBounds().height > window.getSize().y)
        newPosition.y = window.getSize().y - sprite.getGlobalBounds().height;

    sprite.setPosition(newPosition);
}


void Personnage::handleInput(const sf::RenderWindow& window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        move(0, -1, window); // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        move(0, 1, window); // Move down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        move(-1, 0, window); // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        move(1, 0, window); // Move right
    }
}

void Personnage::shoot(std::vector<Projectile>& projectiles, const std::string& projectileTextureFile, const sf::RenderWindow& window) {
    if (canShoot()) {
        // Obtenir la position actuelle du personnage
        sf::Vector2f characterPosition = sprite.getPosition();

        // Obtenir la position du clic de la souris par rapport à la fenêtre
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Calculer la direction du tir (vecteur normalisé)
        sf::Vector2f direction = sf::Vector2f(mousePosition) - characterPosition;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction /= length;
        }

        // Ajouter le projectile avec la direction calculée
        float x = characterPosition.x + sprite.getGlobalBounds().width / 2;
        float y = characterPosition.y + (rand() % 10 - 5); // Ajout d'une légère variation aléatoire en y
        projectiles.emplace_back(projectileTextureFile, x, y, direction * 5.0f); // Vitesse peut être ajustée
        shootClock.restart();
    }
}
bool Personnage::canShoot() {
    return shootClock.getElapsedTime().asSeconds() >= 1.0f / attackSpeed;
}
