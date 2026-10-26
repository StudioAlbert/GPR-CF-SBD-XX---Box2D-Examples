#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "objet.h"

class Ball : public Objet, public sf::Drawable
{
public:
	Ball(b2WorldId world, sf::Vector2f pixel_position);

	void Update();
	void Touche(const Objet& autre) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::CircleShape shape_;
	b2BodyId body_ = b2_nullBodyId;
	int touches_ = 0;
};
