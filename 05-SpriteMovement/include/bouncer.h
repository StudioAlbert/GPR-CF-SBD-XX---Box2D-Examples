#pragma once

#include <SFML/Graphics.hpp>

#include "core/box2DEntity.h"

// Un bord de fenetre. Statique, et visible seulement en mode debug.
class Bouncer : public Box2DEntity
{
public:
	Bouncer(b2WorldId world, sf::Vector2f position, sf::Vector2f size);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape shape_;
};
