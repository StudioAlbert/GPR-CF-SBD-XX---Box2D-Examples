#include "player.h"

#include "SfmlToBox2d.h"

using namespace Utilities;

namespace
{
constexpr float kVitesse = 4.0f;        // m/s
constexpr float kFreinage = 0.9f;       // amortissement quand on lache la touche
}  // namespace

void Player::Init(const sf::Vector2u window_size, const b2WorldId world)
{
	window_size_ = sf::Vector2f(window_size);

	// --- le graphique ------------------------------------------------------
	if (!texture_.loadFromFile("data/playerShip3_blue.png"))
	{
		// Pas d'image : on garde un sprite blanc plutot que de planter, mais on
		// le dit. Un chemin relatif se lit depuis le repertoire de l'executable.
		texture_ = sf::Texture(sf::Vector2u(48, 48));
	}
	shape_.emplace(texture_);
	shape_->setOrigin(sf::Vector2f(texture_.getSize()) * 0.5f);

	const sf::Vector2f depart(window_size_.x * 0.5f, window_size_.y - 40.0f);
	shape_->setPosition(depart);

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_dynamicBody;
	body_def.motionLocks.angularZ = true;
	body_def.linearDamping = kFreinage;
	body_def.position = SfmlToBox2d::PixelsToMeters(depart);
	body_ = b2CreateBody(world, &body_def);

	// --- la forme ----------------------------------------------------------
	// En METRES. Le squelette d'origine passait des pixels ici : le vaisseau
	// faisait une centaine de metres de large, et plus rien ne se comportait
	// normalement.
	const sf::Vector2f demi = sf::Vector2f(texture_.getSize()) * 0.5f;
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

	// On garde le vaisseau dans la fenetre.
	const float demi_largeur = 0.5f * texture_.getSize().x;
	const float gauche = demi_largeur;
	const float droite = window_size_.x - demi_largeur;

	if (position.x < gauche || position.x > droite)
	{
		position.x = std::min(std::max(position.x, gauche), droite);
		b2Body_SetTransform(body_, SfmlToBox2d::PixelsToMeters(position),
		                    b2Body_GetRotation(body_));
		b2Body_SetLinearVelocity(body_, {0.0f, 0.0f});
	}

	shape_->setPosition(position);
}

sf::Vector2f Player::GetVelocity() const
{
	// Par valeur : l'original rendait une reference sur un temporaire.
	return SfmlToBox2d::MetersToPixels(b2Body_GetLinearVelocity(body_));
}

void Player::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
	if (shape_) target.draw(*shape_, states);
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
