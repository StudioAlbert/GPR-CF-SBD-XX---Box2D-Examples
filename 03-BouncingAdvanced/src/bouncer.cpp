#include "bouncer.h"

#include "SFML-Utilities.h"

Bouncer::Bouncer(const b2WorldId world, const sf::Vector2f start, const sf::Vector2f end)
{
	const sf::Vector2f trait = end - start;
	const sf::Vector2f centre = 0.5f * (start + end);

	// L'angle du trait, mesure a l'ecran. Positif = sens horaire, puisque Y
	// descend.
	const float angle_ecran = VecAngle({1.0f, 0.0f}, trait);

	// --- le graphique ------------------------------------------------------
	shape_.setSize({VecLength(trait), MetersToPixels(0.1f)});
	shape_.setOrigin(0.5f * shape_.getSize());
	shape_.setPosition(centre);
	shape_.setRotation(sf::radians(angle_ecran));
	shape_.setFillColor(sf::Color::Cyan);

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_staticBody;
	body_def.position = PixelsToMeters(centre);
	// Le signe s'inverse en passant a l'ecran : ce qui tourne dans un sens
	// la-bas tourne dans l'autre ici. C'est la meme raison que l'axe Y.
	body_def.rotation = b2MakeRot(-angle_ecran);
	body_ = b2CreateBody(world, &body_def);

	// --- la forme ----------------------------------------------------------
	// b2MakeBox prend des DEMI-dimensions, dans le repere du corps : la
	// rotation est deja portee par le corps, la boite n'a pas a la refaire.
	const b2Polygon box = b2MakeBox(PixelsToMeters(shape_.getSize().x) / 2.0f,
	                                PixelsToMeters(shape_.getSize().y) / 2.0f);

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.5f;
	shape_def.material.restitution = 0.6f;

	b2CreatePolygonShape(body_, &shape_def, &box);
}

void Bouncer::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	// Statique : rien ne bouge, rien a recopier depuis le corps.
	target.draw(shape_, states);
}
