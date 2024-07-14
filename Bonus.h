#pragma once
#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>

enum BonusType 
{
	//Speed,
	AttackDamage,
	AttackSpeed,
	HealPoints
};
class Bonus
{
private: 

	BonusType type;
	float value;
	sf::RectangleShape shape;


public:
	Bonus(BonusType type, float value, const sf::Vector2f& position);
	void draw(sf::RenderWindow& window);
	const sf::FloatRect getBounds() const;

	BonusType getType() const;
	float getValue() const;
};

#endif //BONUS_H