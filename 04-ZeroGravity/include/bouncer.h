#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

// Un bord de fenetre. Statique, et solide : la balle rebondit dessus.
class Bouncer : public sf::Drawable
{
public:
	Bouncer(b2WorldId world, sf::Vector2f position, sf::Vector2f size);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape shape_;
	b2BodyId body_ = b2_nullBodyId;
};
