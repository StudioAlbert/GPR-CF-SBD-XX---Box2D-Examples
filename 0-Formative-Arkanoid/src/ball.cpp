#include "ball.h"

#include <limits>
#include <vector>

#include "RNG.h"
#include "SFML_Vectors.h"

namespace
{
constexpr float kRayon = 5.0f;
constexpr float kVitesse = 300.0f;   // px/s
}  // namespace

Ball::Ball(const sf::Vector2u window_size) : shape_(kRayon)
{
	window_size_ = sf::Vector2f(window_size);

	shape_.setOrigin({kRayon, kRayon});

	direction_ = Utilities::SFML_Vectors::Normalize(
	    {Utilities::RNG::Range(-1.0f, 1.0f), Utilities::RNG::Range(-1.0f, 1.0f)});

	shape_.setPosition(window_size_ * 0.5f);
}

void Ball::Update(const float time_elapsed)
{
	velocity_ = direction_ * kVitesse;
	shape_.setPosition(shape_.getPosition() + velocity_ * time_elapsed);
}

void Ball::CollideBounds()
{
	const sf::Vector2f p = shape_.getPosition();

	if (p.x <= 0.0f) Bounce(Utilities::SFML_Vectors::RIGHT);
	if (p.x >= window_size_.x) Bounce(Utilities::SFML_Vectors::LEFT);
	if (p.y <= 0.0f) Bounce(Utilities::SFML_Vectors::DOWN);
}

bool Ball::Collide(const sf::FloatRect& bounds)
{
	const sf::Vector2f avance =
	    Utilities::SFML_Vectors::Normalize(velocity_) * shape_.getRadius();

	// TO DO : un seul point teste devant la balle. A grande vitesse elle peut
	// traverser une brique entre deux images — comment l'eviter ?
	if (bounds.contains(shape_.getPosition() + avance))
	{
		Bounce(ContactNormal(bounds, avance));

		// Fausse separation : on pousse la balle hors de la brique pour ne pas
		// rebondir deux fois de suite sur la meme.
		shape_.setPosition(shape_.getPosition() + direction_ * 3.0f * shape_.getRadius());
		return true;
	}

	return false;
}

sf::Vector2f Ball::ContactNormal(const sf::FloatRect& bounds, const sf::Vector2f direction)
{
	using namespace Utilities::SFML_Vectors;

	// Les quatre cotes du rectangle, parcourus dans le sens horaire.
	const std::vector<sf::Vector2f> cotes = {
	    {bounds.size.x, 0.0f},
	    {0.0f, bounds.size.y},
	    {-bounds.size.x, 0.0f},
	    {0.0f, -bounds.size.y},
	};

	// TO DO : trouver le bon cote. Le produit scalaire le plus petit designe le
	// cote le plus oppose a la direction d'arrivee — est-ce toujours vrai ?
	sf::Vector2f meilleur;
	float meilleur_produit = std::numeric_limits<float>::max();

	for (const sf::Vector2f cote : cotes)
	{
		const float produit = Dot(direction, cote);
		if (produit < meilleur_produit)
		{
			meilleur_produit = produit;
			meilleur = cote;
		}
	}

	return Normalize(LeftOrtho(meilleur));
}

void Ball::Bounce(const sf::Vector2f direction)
{
	constexpr float kEpsilon = std::numeric_limits<float>::epsilon();

	if (std::abs(direction.x) > kEpsilon) direction_.x *= -1.0f;
	if (std::abs(direction.y) > kEpsilon) direction_.y *= -1.0f;

	direction_ *= 1.025f;   // 2,5 % plus vite a chaque rebond
}

bool Ball::IsOut() const
{
	return shape_.getPosition().y >= window_size_.y;
}

void Ball::AddForce(const sf::Vector2f force)
{
	direction_ += force;
}

void Ball::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	target.draw(shape_, states);
}
