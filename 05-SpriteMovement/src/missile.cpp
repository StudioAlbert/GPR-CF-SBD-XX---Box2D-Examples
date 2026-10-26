#include "missile.h"

#include "core/SFML_Utilities.h"
#include "managers/textureManager.h"

namespace
{
constexpr float kVitesse = 8.0f;   // m/s
}  // namespace

long Missile::NextId()
{
	static long suivant = 0;
	return suivant++;
}

Missile::Missile(const b2WorldId world, const sf::Vector2f start_pixels, const sf::Angle angle)
    : Box2DEntity(world)
{
	const sf::Texture& texture = TextureManager::Instance().Missile();

	sprite_.emplace(texture);
	sprite_->setOrigin(sf::Vector2f(texture.getSize()) * 0.5f);

	user_data_.SetType(UserDataType::Missile);
	user_data_.SetLocalId(NextId());

	// --- le corps ----------------------------------------------------------
	b2Body_SetType(body_, b2_kinematicBody);   // rien ne le devie
	b2Body_SetAngularDamping(body_, 0.0f);
	b2Body_SetLinearDamping(body_, 0.0f);

	// L'angle du vaisseau est un angle d'ECRAN : il s'inverse pour le monde.
	const float angle_monde = -angle.asRadians();
	b2Body_SetTransform(body_, PixelsToMeters(start_pixels), b2MakeRot(angle_monde));

	// Le vaisseau pointe vers le haut, donc le missile part vers son +Y local.
	b2Body_SetLinearVelocity(body_, b2Body_GetWorldVector(body_, {0.0f, kVitesse}));

	// --- la forme ----------------------------------------------------------
	const sf::Vector2f demi = sf::Vector2f(texture.getSize()) * 0.5f;
	const b2Polygon box = b2MakeBox(PixelsToMeters(demi.x), PixelsToMeters(demi.y));

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.isSensor = true;
	// Les DEUX formes doivent l'activer : celle-ci et celle de l'asteroide.
	shape_def.enableSensorEvents = true;

	b2CreatePolygonShape(body_, &shape_def, &box);

	Update();
}

void Missile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (sprite_) target.draw(*sprite_, states);
}
