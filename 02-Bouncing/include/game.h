#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "ball.h"
#include "bouncer.h"

// Une bille qui rebondit sur une plateforme statique, et qui change de couleur a
// chaque contact. C'est la demonstration des contacts en Box2D 3.
class Game
{
public:
	Game();
	~Game();

	void Init();
	void Loop();

	b2WorldId GetWorld() const { return world_; }

	static b2Vec2 PixelsToMeters(sf::Vector2f pixels);
	static b2Vec2 PixelsToMeters(sf::Vector2u pixels);
	static float PixelsToMeters(float pixels);

	static sf::Vector2f MetersToPixels(b2Vec2 meters);
	static float MetersToPixels(float meters);

	static constexpr float pixels_meters_ratio_ = 100.0f;

private:
	sf::RenderWindow window_;

	b2WorldId world_ = b2_nullWorldId;

	Ball the_ball_;
	Bouncer bouncer_;
};
