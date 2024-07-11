#include "Projectile.h"
#include <iostream>

Projectile::Projectile(const std::string& textureFile, float x, float y, const sf::Vector2f& velocity) : velocity(velocity) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Error loading projectile texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Projectile::update() {
    sprite.move(velocity); // Déplacement selon la vitesse et direction actuelles
}

void Projectile::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Projectile::getPosition() const {
    return sprite.getPosition();
}

sf::FloatRect Projectile::getBounds() const {
    return sprite.getGlobalBounds();
}
