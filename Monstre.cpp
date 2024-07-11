#include "Monstre.h"
#include <iostream>

// Default constructor
Monstre::Monstre() : name("Goblin"), healthPoints(100), attackDamage(15) {
    std::cout << "Default constructor called" << std::endl;
}

// Parameterized constructor
Monstre::Monstre(const std::string& n, int hp, int ad,float as, const std::string& textureFile)
    : name(n), healthPoints(hp), attackDamage(ad), alive(true), speed(as) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture" << std::endl;
    }
    sprite.setTexture(texture);
}

// Method to display monster information
void Monstre::displayMonstre() const {
    std::cout << "Name: " << name
        << ", HP: " << healthPoints
        << ", AD: " << attackDamage
        << ", MS: " << speed
        << std::endl;
}

// Method to receive damage
void Monstre::receiveDamage(int damage) {
    healthPoints -= damage;
    if (healthPoints <= 0) {
        healthPoints = 0;
        alive = false; // Set alive to false if health points reach zero
        std::cout << name << " is dead!" << std::endl;
    }
}

void Monstre::move(float offsetX, float offsetY, const sf::RenderWindow& window) {
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

void Monstre::moveTowards(const sf::Vector2f& targetPosition, float deltaTime) {
    sf::Vector2f currentPosition = sprite.getPosition();
    sf::Vector2f direction = targetPosition - currentPosition;

    // Normalisation du vecteur de direction
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
    }

    // Calcul du déplacement en fonction de la vitesse et du deltaTime
    sf::Vector2f movement = direction * speed * deltaTime;

    // Appliquer le déplacement
    sprite.move(movement);
}

// Accessors
std::string Monstre::getName() const {
    return name;
}

int Monstre::getHealthPoints() const {
    return healthPoints;
}

float Monstre::getSpeed() const
{
    return speed;
}

int Monstre::getAttackDamage() const
{
    return attackDamage;
}

bool Monstre::isAlive() const {
    return alive;
}

sf::Vector2f Monstre::getPosition() const
{
    return sprite.getPosition();
}

// SFML Methods
void Monstre::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Monstre::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::FloatRect Monstre::getBounds() const {
    return sprite.getGlobalBounds();
}