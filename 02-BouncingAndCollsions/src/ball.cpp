#include "ball.h"

#include "RNG.h"
#include "SfmlToBox2d.h"

using namespace Utilities;

Ball::Ball(const b2WorldId world, const sf::Vector2f pixel_position)
    : Objet(TypeObjet::Balle), shape_(20.0f)
{
	// --- le graphique ------------------------------------------------------
	shape_.setOrigin({shape_.getRadius(), shape_.getRadius()});
	shape_.setFillColor(sf::Color::Green);

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_dynamicBody;
	body_def.motionLocks.angularZ = true;
	body_def.position = SfmlToBox2d::PixelsToMeters(pixel_position);
	body_ = b2CreateBody(world, &body_def);

	b2Body_SetLinearVelocity(body_, {RNG::Range(-3.0f, 3.0f), RNG::Range(-3.0f, 3.0f)});

	// --- la forme ----------------------------------------------------------
	b2Circle circle{};
	circle.center = {0.0f, 0.0f};
	circle.radius = SfmlToBox2d::PixelsToMeters(shape_.getRadius());

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.0f;
	shape_def.material.restitution = 1.0f;   // elle ne perd rien
	shape_def.enableContactEvents = true;

	// L'etiquette part par la base commune : c'est ce qui rend le cast du
	// lecteur de contacts sur : tout ce qui sort de `userData` EST un `Objet`.
	shape_def.userData = static_cast<Objet*>(this);

	b2CreateCircleShape(body_, &shape_def, &circle);
}

void Ball::Update()
{
	shape_.setPosition(SfmlToBox2d::MetersToPixels(b2Body_GetPosition(body_)));
}

void Ball::Touche(const Objet& autre)
{
	if (autre.Type() != TypeObjet::Mur) return;

	// Elle palit a chaque mur touche : au bout de cinq, elle est blanche.
	++touches_;
	const auto reste = static_cast<std::uint8_t>(255 - std::min(touches_, 5) * 40);
	shape_.setFillColor(sf::Color(255 - reste, 255, 255 - reste));
}

void Ball::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(shape_, states);
}
