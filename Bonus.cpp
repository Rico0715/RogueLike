#include "Bonus.h"


Bonus::Bonus(BonusType type, float value, const sf::Vector2f& position)
    : type(type), value(value) {
    shape.setSize({20.0f, 20.0f});
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Yellow); // Couleur jaune pour les bonus
}

void Bonus::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

const sf::FloatRect Bonus::getBounds() const {
    return shape.getGlobalBounds();
}

BonusType Bonus::getType() const {
    return type;
}

float Bonus::getValue() const {
    return value;
}
