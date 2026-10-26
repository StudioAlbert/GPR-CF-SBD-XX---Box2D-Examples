#include "ball.h"

#include <iostream>

#include "game.h"

Ball::Ball(Game& game, sf::RenderWindow& window) : game_(game), window_(window)
{
}

void Ball::Init()
{
	// --- le graphique ------------------------------------------------------
	shape_.setRadius(Game::MetersToPixels(0.2f));
	shape_.setOrigin({shape_.getRadius(), shape_.getRadius()});
	shape_.setFillColor(sf::Color::Red);

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_dynamicBody;
	// Box2D 3 : `fixedRotation` de la version 2 est devenu un verrou de mouvement.
	body_def.motionLocks.angularZ = true;

	const b2Vec2 window_size = Game::PixelsToMeters(window_.getSize());
	body_def.position = {window_size.x / 2.0f, window_size.y / 2.0f};
	body_ = b2CreateBody(game_.GetWorld(), &body_def);

	// --- la forme, et sa matiere -------------------------------------------
	// La fixture a disparu : la forme et sa matiere sont une seule structure.
	b2Circle circle{};
	circle.center = {0.0f, 0.0f};
	circle.radius = Game::PixelsToMeters(shape_.getRadius());

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.0f;
	b2CreateCircleShape(body_, &shape_def, &circle);
}

void Ball::Update()
{
	// La copie va du physique vers le graphique, jamais l'inverse.
	const b2Vec2 body_position = b2Body_GetPosition(body_);
	shape_.setPosition(Game::MetersToPixels(body_position));

	std::cout << "corps [" << body_position.x << " ; " << body_position.y << "] m  ->  sprite ["
	          << shape_.getPosition().x << " ; " << shape_.getPosition().y << "] px\n";
}

void Ball::Render()
{
	window_.draw(shape_);
}

void Ball::SetPixelsPosition(sf::Vector2f pixels_position)
{
	// Teleporter, puis remettre la vitesse a zero : sinon la bille garde son elan.
	b2Body_SetTransform(body_, Game::PixelsToMeters(pixels_position), b2Body_GetRotation(body_));
	b2Body_SetLinearVelocity(body_, {0.0f, 0.0f});
}
