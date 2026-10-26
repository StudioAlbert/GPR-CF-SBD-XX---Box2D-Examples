#include "bouncer.h"

#include "SFML_Utilities.h"

Bouncer::Bouncer(const b2WorldId world, const sf::Vector2f position, const sf::Vector2f size)
{
	// --- le graphique ------------------------------------------------------
	shape_.setSize(size);
	shape_.setOrigin(0.5f * size);
	shape_.setPosition(position);
	shape_.setFillColor(sf::Color::Cyan);

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_staticBody;
	body_def.position = PixelsToMeters(position);
	body_ = b2CreateBody(world, &body_def);

	// --- la forme ----------------------------------------------------------
	// b2MakeBox prend des DEMI-dimensions.
	const b2Polygon box =
	    b2MakeBox(PixelsToMeters(size.x) / 2.0f, PixelsToMeters(size.y) / 2.0f);

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.0f;
	shape_def.material.restitution = 1.0f;

	b2CreatePolygonShape(body_, &shape_def, &box);
}

void Bouncer::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	// Statique : la forme ne bouge jamais, rien a recopier depuis le corps.
	target.draw(shape_, states);
}
