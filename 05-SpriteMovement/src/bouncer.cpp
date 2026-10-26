#include "bouncer.h"

#include "core/SFML_Utilities.h"

Bouncer::Bouncer(const b2WorldId world, const sf::Vector2f position, const sf::Vector2f size)
    : Box2DEntity(world)
{
	user_data_.SetType(UserDataType::Limit);

	// --- le graphique ------------------------------------------------------
	shape_.setSize(size);
	shape_.setOrigin(size * 0.5f);
	shape_.setFillColor(sf::Color(200, 60, 60, 120));

	// --- le corps ----------------------------------------------------------
	b2Body_SetType(body_, b2_staticBody);
	b2Body_SetTransform(body_, PixelsToMeters(position), b2Rot_identity);

	// --- la forme ----------------------------------------------------------
	// b2MakeBox prend des DEMI-dimensions. L'original passait la taille
	// entiere, donc les bords debordaient de moitie hors de la fenetre.
	const b2Polygon box = b2MakeBox(PixelsToMeters(size.x) * 0.5f,
	                                PixelsToMeters(size.y) * 0.5f);

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.2f;
	shape_def.material.restitution = 0.01f;

	b2CreatePolygonShape(body_, &shape_def, &box);

	// Le graphique ne bougera plus : on le place une fois.
	Update();
	shape_.setPosition(getPosition());
}

void Bouncer::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(shape_, states);
}
