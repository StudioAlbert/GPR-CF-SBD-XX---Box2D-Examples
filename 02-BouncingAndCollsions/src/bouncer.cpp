#include "bouncer.h"

#include <algorithm>

#include "SfmlToBox2d.h"

using namespace Utilities;

namespace
{
constexpr float kDureeEclat = 0.25f;   // s
}  // namespace

Bouncer::Bouncer(const b2WorldId world, const sf::Vector2f position, const sf::Vector2f size)
    : Objet(TypeObjet::Mur)
{
	// --- le graphique ------------------------------------------------------
	shape_.setSize(size);
	shape_.setOrigin(size * 0.5f);
	shape_.setPosition(position);
	shape_.setFillColor(sf::Color(40, 70, 90));

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_staticBody;
	body_def.position = SfmlToBox2d::PixelsToMeters(position);
	body_ = b2CreateBody(world, &body_def);

	// --- la forme ----------------------------------------------------------
	const b2Polygon box = b2MakeBox(SfmlToBox2d::PixelsToMeters(size.x) * 0.5f,
	                                SfmlToBox2d::PixelsToMeters(size.y) * 0.5f);

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.0f;
	shape_def.material.restitution = 1.0f;
	// Pas de `enableContactEvents` : un corps statique ne peut pas le porter,
	// et la balle l'active deja — une seule des deux formes suffit.
	shape_def.userData = static_cast<Objet*>(this);

	b2CreatePolygonShape(body_, &shape_def, &box);
}

void Bouncer::Update(const float dt)
{
	eclat_ = std::max(0.0f, eclat_ - dt);

	const float t = eclat_ / kDureeEclat;
	shape_.setFillColor(sf::Color(static_cast<std::uint8_t>(40 + 180 * t),
	                              static_cast<std::uint8_t>(70 + 160 * t),
	                              static_cast<std::uint8_t>(90 + 150 * t)));
}

void Bouncer::Touche(const Objet& autre)
{
	if (autre.Type() == TypeObjet::Balle) eclat_ = kDureeEclat;
}

void Bouncer::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(shape_, states);
}
