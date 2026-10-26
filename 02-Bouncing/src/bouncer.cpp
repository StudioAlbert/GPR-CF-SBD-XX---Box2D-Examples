#include "bouncer.h"

#include "game.h"

Bouncer::Bouncer(Game& game, sf::RenderWindow& window) : game_(game), window_(window)
{
}

void Bouncer::Init()
{
	// --- le graphique ------------------------------------------------------
	// 2 metres de long, 0,5 metre de haut.
	const b2Vec2 physical_size{2.0f, 0.5f};
	shape_.setSize(Game::MetersToPixels(physical_size));
	shape_.setOrigin(0.5f * shape_.getSize());
	shape_.setFillColor(sf::Color::Cyan);

	// --- le corps ----------------------------------------------------------
	b2BodyDef body_def = b2DefaultBodyDef();
	body_def.type = b2_staticBody;   // statique : rien ne la deplace

	const b2Vec2 position = Game::PixelsToMeters(
	    sf::Vector2f(0.5f * window_.getSize().x, window_.getSize().y - 100.0f));
	body_def.position = position;
	body_ = b2CreateBody(game_.GetWorld(), &body_def);

	// --- la forme, et sa matiere -------------------------------------------
	// b2MakeBox prend des DEMI-dimensions.
	const b2Polygon box = b2MakeBox(physical_size.x / 2.0f, physical_size.y / 2.0f);

	b2ShapeDef shape_def = b2DefaultShapeDef();
	shape_def.density = 1.0f;
	shape_def.material.friction = 0.5f;
	shape_def.material.restitution = 0.6f;
	// Pas de enableContactEvents ici : un corps statique ne peut pas le porter,
	// et de toute facon une seule des deux formes suffit.

	b2CreatePolygonShape(body_, &shape_def, &box);
}

void Bouncer::Update()
{
	shape_.setPosition(Game::MetersToPixels(b2Body_GetPosition(body_)));
}

void Bouncer::Render() const
{
	window_.draw(shape_);
}
