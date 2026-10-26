#include "ship.h"

#include "core/SFML_Utilities.h"
#include "managers/textureManager.h"

Ship::Ship(const b2WorldId world) : Box2DEntity(world)
{
	const sf::Texture& texture = TextureManager::Instance().Ship();

	sprite_.emplace(texture);
	sprite_->setOrigin(sf::Vector2f(texture.getSize()) * 0.5f);

	user_data_.SetType(UserDataType::Ship);

	// --- la forme ----------------------------------------------------------
	// En METRES, une seule fois. L'original convertissait deja en appelant
	// createFixture, puis reconvertissait dedans.
	const sf::Vector2f demi = sf::Vector2f(texture.getSize()) * 0.5f;
	const b2Polygon box = b2MakeBox(PixelsToMeters(demi.x), PixelsToMeters(demi.y));

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.0f;
	shape_def.material.restitution = 0.6f;
	shape_def.enableContactEvents = true;   // sinon : aucun choc detecte

	b2CreatePolygonShape(body_, &shape_def, &box);
}

void Ship::Init(const sf::Vector2u window_size)
{
	const sf::Vector2f centre(0.5f * window_size.x, 0.5f * window_size.y);
	b2Body_SetTransform(body_, PixelsToMeters(centre), b2Rot_identity);

	b2Body_SetLinearDamping(body_, 0.5f);
	b2Body_SetAngularDamping(body_, 0.25f);
}

void Ship::Update()
{
	Box2DEntity::Update();

	// Sous le seuil, on arrete net : sinon le vaisseau derive indefiniment.
	if (VecLength(b2Body_GetLinearVelocity(body_)) < kEpsilon)
	{
		b2Body_SetLinearVelocity(body_, {0.0f, 0.0f});
	}
}

void Ship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (sprite_) target.draw(*sprite_, states);
}

void Ship::SpeedUp(const float force)
{
	ApplyLocalForce(force);
}

void Ship::SpeedDown(const float damping)
{
	b2Body_SetLinearDamping(body_, damping);
}

void Ship::ApplyLocalForce(const float force)
{
	b2Body_SetLinearDamping(body_, 0.5f);

	// La poussee est dans le repere du vaisseau : il avance la ou il pointe.
	const b2Vec2 poussee = b2Body_GetWorldVector(body_, {0.0f, force});

	if (VecLength(b2Body_GetLinearVelocity(body_)) < kMaxLinearVelocity)
	{
		b2Body_ApplyForceToCenter(body_, poussee, true);
	}
}

void Ship::RotateLeft(const float torque) { ApplyTorque(torque); }
void Ship::RotateRight(const float torque) { ApplyTorque(-torque); }

void Ship::ApplyTorque(const float torque)
{
	SetAngularDamping(0.5f);

	const float vitesse = b2Body_GetAngularVelocity(body_);
	if ((torque > 0.0f && vitesse < kMaxAngularVelocity) ||
	    (torque < 0.0f && vitesse > -kMaxAngularVelocity))
	{
		b2Body_ApplyTorque(body_, torque, true);
	}
}

void Ship::SetAngularDamping(const float damping)
{
	b2Body_SetAngularDamping(body_, damping);
}
