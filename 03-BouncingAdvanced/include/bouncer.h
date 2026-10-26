#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

// Une plateforme INCLINEE, tracee a la souris. C'est le seul exemple du depot
// ou un corps a une rotation : il montre pourquoi l'angle change de signe entre
// le monde physique et l'ecran.
class Bouncer : public sf::Drawable
{
public:
	Bouncer(b2WorldId world, sf::Vector2f start, sf::Vector2f end);

	b2BodyId GetBody() const { return body_; }
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape shape_;
	b2BodyId body_ = b2_nullBodyId;
};
