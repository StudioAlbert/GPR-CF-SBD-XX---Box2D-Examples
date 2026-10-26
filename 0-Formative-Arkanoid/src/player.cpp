#include "player.h"

#include <algorithm>

#include "SfmlToBox2d.h"

using namespace Utilities;

namespace
{
constexpr float kVitesse = 4.0f;    // m/s
constexpr float kFreinage = 0.5f;
}  // namespace

void Player::Init(const sf::Vector2u window_size, const b2WorldId world)
{
	window_size_ = sf::Vector2f(window_size);

	// --- le graphique ------------------------------------------------------
	shape_.setSize({60.0f, 12.0f});
	shape_.setOrigin(shape_.getSize() * 0.5f);
	shape_.setFillColor(sf::Color(75, 30, 37));
	shape_.setOutlineColor(sf::Color(150, 60, 74));
	shape_.setOutlineThickness(1.0f);

	const sf::Vector2f depart(window_size_.x * 0.5f, window_size_.y - 40.0f);
	shape_.setPosition(depart);

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_dynamicBody;
	body_def.motionLocks.angularZ = true;
	body_def.linearDamping = kFreinage;
	body_def.position = SfmlToBox2d::PixelsToMeters(depart);
	body_ = b2CreateBody(world, &body_def);

	// --- la forme ----------------------------------------------------------
	const sf::Vector2f demi = shape_.getSize() * 0.5f;
	const b2Polygon box = b2MakeBox(SfmlToBox2d::PixelsToMeters(demi.x),
	                                SfmlToBox2d::PixelsToMeters(demi.y));

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.3f;
	b2CreatePolygonShape(body_, &shape_def, &box);
}

void Player::Update()
{
	sf::Vector2f position = SfmlToBox2d::MetersToPixels(b2Body_GetPosition(body_));

	const float demi_largeur = 0.5f * shape_.getSize().x;
	const float serre = std::clamp(position.x, demi_largeur, window_size_.x - demi_largeur);

	if (serre != position.x)
	{
		position.x = serre;
		b2Body_SetTransform(body_, SfmlToBox2d::PixelsToMeters(position),
		                    b2Body_GetRotation(body_));
		b2Body_SetLinearVelocity(body_, {0.0f, 0.0f});
	}

	shape_.setPosition(position);
}

sf::Vector2f Player::GetVelocity() const
{
	return SfmlToBox2d::MetersToPixels(b2Body_GetLinearVelocity(body_));
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(shape_, states);
}

void Player::MoveLeft()
{
	b2Body_SetLinearVelocity(body_, {-kVitesse, 0.0f});
	b2Body_SetLinearDamping(body_, 0.0f);
	b2Body_SetAwake(body_, true);
}

void Player::MoveRight()
{
	b2Body_SetLinearVelocity(body_, {kVitesse, 0.0f});
	b2Body_SetLinearDamping(body_, 0.0f);
	b2Body_SetAwake(body_, true);
}

void Player::Stop()
{
	b2Body_SetLinearDamping(body_, kFreinage);
}
