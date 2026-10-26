#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "objet.h"

// Un mur. Statique, et il s'allume quand une balle le touche.
class Bouncer : public Objet, public sf::Drawable
{
public:
	Bouncer(b2WorldId world, sf::Vector2f position, sf::Vector2f size);

	void Update(float dt);
	void Touche(const Objet& autre) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape shape_;
	b2BodyId body_ = b2_nullBodyId;
	float eclat_ = 0.0f;   // secondes restantes d'illumination
};
