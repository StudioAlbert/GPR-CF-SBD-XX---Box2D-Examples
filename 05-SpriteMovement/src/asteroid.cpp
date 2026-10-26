#include "asteroid.h"

#include <numbers>
#include <random>

#include "core/SFML_Utilities.h"
#include "managers/textureManager.h"

namespace
{

std::mt19937& Generateur()
{
	static std::random_device source;
	static std::mt19937 generateur(source());
	return generateur;
}

}  // namespace

long Asteroid::NextId()
{
	static long suivant = 0;
	return suivant++;
}

Asteroid::Asteroid(const b2WorldId world, const sf::Vector2f window_size) : Box2DEntity(world)
{
	const sf::Texture& texture = TextureManager::Instance().Asteroid();

	sprite_.emplace(texture);
	sprite_->setOrigin(sf::Vector2f(texture.getSize()) * 0.5f);

	user_data_.SetType(UserDataType::Asteroid);
	user_data_.SetLocalId(NextId());

	// --- la forme ----------------------------------------------------------
	b2Circle cercle{};
	cercle.center = {0.0f, 0.0f};
	cercle.radius = PixelsToMeters(0.5f * texture.getSize().x);

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.0f;
	shape_def.material.restitution = 1.0f;
	shape_def.enableContactEvents = true;   // pour le choc avec le vaisseau
	shape_def.enableSensorEvents = true;    // pour etre vu par le missile

	b2CreateCircleShape(body_, &shape_def, &cercle);

	// --- ou, comment, et dans quel sens ------------------------------------
	std::uniform_real_distribution<float> position_x(0.0f, window_size.x);
	std::uniform_real_distribution<float> position_y(0.0f, window_size.y);
	std::uniform_real_distribution<float> angle(0.0f, 2.0f * std::numbers::pi_v<float>);
	std::uniform_real_distribution<float> poussee(-0.1f, 0.1f);

	// L'angle en RADIANS. L'original tirait un entier entre 0 et 360 et le
	// passait tel quel : cinquante-sept tours.
	b2Body_SetTransform(body_,
	                    PixelsToMeters(sf::Vector2f(position_x(Generateur()),
	                                                position_y(Generateur()))),
	                    b2MakeRot(angle(Generateur())));

	b2Body_ApplyLinearImpulseToCenter(body_, {poussee(Generateur()), poussee(Generateur())}, true);

	b2Body_SetLinearDamping(body_, 0.0f);
	b2Body_SetAngularDamping(body_, 0.0f);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (sprite_) target.draw(*sprite_, states);
}
