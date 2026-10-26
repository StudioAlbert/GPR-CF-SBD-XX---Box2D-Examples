#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

// Un vrai capteur : il detecte, il n'arrete rien. La balle le traverse et il
// s'allume. C'est la difference avec un contact, et c'est la reponse a
// « est-ce que je touche le sol » en SBD-06.
class Sensor : public sf::Drawable
{
public:
	Sensor(b2WorldId world, sf::Vector2f position, float radius);

	b2BodyId GetBody() const { return body_; }
	void SetColor(sf::Color color);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::CircleShape shape_;
	b2BodyId body_ = b2_nullBodyId;
};
