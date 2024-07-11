#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>

class Projectile {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity; // Nouvelle variable pour la vitesse et direction du projectile


public:
    Projectile(const std::string& textureFile, float x, float y, const sf::Vector2f& velocity);

    void update();

    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;

    sf::FloatRect getBounds() const;  // New method to get the bounding box

};

#endif // PROJECTILE_H
