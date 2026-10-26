#include "ball.h"

#include "SFML_Utilities.h"

Ball::Ball(sf::RenderWindow& window) : window_(window)
{
}

void Ball::Init(const b2WorldId world)
{
	// --- le graphique ------------------------------------------------------
	shape_.setRadius(20.0f);
	shape_.setOrigin({shape_.getRadius(), shape_.getRadius()});
	shape_.setFillColor(sf::Color::Red);

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_dynamicBody;
	body_def.motionLocks.angularZ = true;
	body_def.position = PixelsToMeters(sf::Vector2f(640.0f, 360.0f));
	body_ = b2CreateBody(world, &body_def);

	// --- la forme ----------------------------------------------------------
	b2Circle circle{};
	circle.center = {0.0f, 0.0f};
	circle.radius = PixelsToMeters(shape_.getRadius());

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.0f;
	shape_def.material.restitution = 1.0f;  // elle ne perd rien sur les bords

	// Pour un capteur, les DEUX formes doivent l'activer : celle du capteur et
	// celle du visiteur. C'est la difference avec `enableContactEvents`, ou une
	// seule suffit.
	shape_def.enableSensorEvents = true;

	b2CreateCircleShape(body_, &shape_def, &circle);
}

void Ball::Update()
{
	shape_.setPosition(MetersToPixels(b2Body_GetPosition(body_)));
}

void Ball::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(shape_, states);
}

void Ball::SetPixelsPosition(const sf::Vector2f pixels_position, const sf::Vector2f velocity) const
{
	b2Body_SetTransform(body_, PixelsToMeters(pixels_position), b2Body_GetRotation(body_));
	b2Body_SetLinearVelocity(body_, PixelsToMeters(velocity));
	b2Body_SetAwake(body_, true);
}

void Ball::Move(const float x, const float y) const
{
	b2Body_SetLinearVelocity(body_, {x, y});
	b2Body_SetAwake(body_, true);
}
