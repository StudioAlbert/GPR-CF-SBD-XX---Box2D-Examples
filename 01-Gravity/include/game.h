#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ball.h"

// Le monde physique et le monde graphique, cote a cote. Le facteur de conversion
// vit ici et nulle part ailleurs : le jour ou il change, il ne change qu'une fois.
class Game
{
public:
	Game();
	~Game();

	void Init();
	void Loop();

	// En Box2D 3 le monde est un identifiant, pas un objet : on le copie sans crainte.
	b2WorldId GetWorld() const { return world_; }

	static b2Vec2 PixelsToMeters(sf::Vector2f pixels);
	static b2Vec2 PixelsToMeters(sf::Vector2u pixels);
	static float PixelsToMeters(float pixels);

	static sf::Vector2f MetersToPixels(b2Vec2 meters);
	static float MetersToPixels(float meters);

	static constexpr float pixels_meters_ratio_ = 100.0f;

private:
	sf::RenderWindow window_;

	// Cree dans Init(), detruit dans le destructeur. b2DestroyWorld emporte les
	// corps et les formes avec lui : il n'y a rien d'autre a liberer.
	b2WorldId world_ = b2_nullWorldId;

	Ball the_ball_;
};
