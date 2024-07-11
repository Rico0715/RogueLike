#pragma once
#ifndef MONSTRE_H
#define MONSTRE_H

#include <SFML/Graphics.hpp>
#include <string>

class Monstre {
private:
    std::string name;
    int healthPoints;
    int attackDamage;
    bool alive;
    float speed;


    // SFML attributes
    sf::Sprite sprite;
    sf::Texture texture;

public:
    // Constructors
    Monstre();
    Monstre(const std::string& n, int hp, int ad,float ms, const std::string& textureFile);

    // Methods
    void displayMonstre() const;
    void receiveDamage(int damage);
    void move(float offsetX, float offsetY, const sf::RenderWindow& window);
    void moveTowards(const sf::Vector2f& targetPosition, float deltaTime); // Méthode pour déplacer le monstre vers une position cible


    // Accessors and Mutators
    std::string getName() const;
    int getHealthPoints() const;
    float getSpeed()const;
    int getAttackDamage()const;


    // SFML Methods
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::FloatRect getBounds() const;  // New method to get the bounding box
    bool isAlive() const; // New method to check if the monster is alive
    sf::Vector2f getPosition() const;


};

#endif // MONSTRE_H
