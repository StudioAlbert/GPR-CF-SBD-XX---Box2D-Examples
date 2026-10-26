#include "sensor.h"

#include "SFML_Utilities.h"

Sensor::Sensor(const b2WorldId world, const sf::Vector2f position, const float radius)
{
	// --- le graphique ------------------------------------------------------
	shape_.setRadius(radius);
	shape_.setOrigin({radius, radius});
	shape_.setPosition(position);
	shape_.setFillColor(sf::Color::Cyan);

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_staticBody;
	body_def.position = PixelsToMeters(position);
	body_ = b2CreateBody(world, &body_def);

	// --- la forme ----------------------------------------------------------
	b2Circle circle{};
	circle.center = {0.0f, 0.0f};
	circle.radius = PixelsToMeters(radius);

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.isSensor = true;            // il detecte, il n'arrete rien
	shape_def.enableSensorEvents = true;  // sans ca : aucun evenement
	shape_def.userData = this;            // le fil de retour vers cet objet

	b2CreateCircleShape(body_, &shape_def, &circle);
}

void Sensor::SetColor(const sf::Color color)
{
	shape_.setFillColor(color);
}

void Sensor::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(shape_, states);
}
