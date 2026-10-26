#include "ball.h"

#include <cstdlib>

#include "game.h"

Ball::Ball(Game& game, sf::RenderWindow& window) : game_(game), window_(window)
{
}

void Ball::Init()
{
	// --- le graphique ------------------------------------------------------
	shape_.setRadius(20.0f);
	shape_.setOrigin({shape_.getRadius(), shape_.getRadius()});
	shape_.setFillColor(sf::Color::Red);

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_dynamicBody;
	body_def.motionLocks.angularZ = true;

	const b2Vec2 window_size = Game::PixelsToMeters(window_.getSize());
	body_def.position = {window_size.x / 2.0f, window_size.y / 2.0f};
	body_ = b2CreateBody(game_.GetWorld(), &body_def);

	// --- la forme, sa matiere, et son fil vers l'objet de jeu ---------------
	b2Circle circle{};
	circle.center = {0.0f, 0.0f};
	circle.radius = Game::PixelsToMeters(shape_.getRadius());

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.0f;
	shape_def.material.restitution = 0.6f;   // elle rebondit un peu

	// Le piege de Box2D 3 : sans ca, la boucle d'evenements tourne a vide.
	// Une seule des deux formes doit l'activer, et seulement sur un corps
	// cinematique ou dynamique — la plateforme est statique, donc c'est ici.
	shape_def.enableContactEvents = true;

	// Le fil qui ramene de la forme physique a cet objet.
	shape_def.userData = this;

	b2CreateCircleShape(body_, &shape_def, &circle);
}

void Ball::Update()
{
	shape_.setPosition(Game::MetersToPixels(b2Body_GetPosition(body_)));
}

void Ball::Render() const
{
	window_.draw(shape_);
}

void Ball::SetPixelsPosition(const sf::Vector2f pixels_position) const
{
	b2Body_SetTransform(body_, Game::PixelsToMeters(pixels_position), b2Body_GetRotation(body_));
	b2Body_SetLinearVelocity(body_, {0.0f, 0.0f});
	// Sans ca elle reste endormie en l'air : un corps au repos est mis en sommeil.
	b2Body_SetAwake(body_, true);
}

void Ball::SetNewColor()
{
	shape_.setFillColor(sf::Color(static_cast<std::uint8_t>(std::rand() % 256),
	                              static_cast<std::uint8_t>(std::rand() % 256),
	                              static_cast<std::uint8_t>(std::rand() % 256)));
}
