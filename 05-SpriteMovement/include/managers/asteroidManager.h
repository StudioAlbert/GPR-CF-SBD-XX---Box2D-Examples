#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "asteroid.h"

class AsteroidManager : public sf::Drawable
{
public:
	explicit AsteroidManager(b2WorldId world) : world_(world) {}

	void Update();
	void AddAsteroid(sf::Vector2f window_size);
	void PutAsteroidToDeath(long id);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	// Des `unique_ptr` : Box2D garde l'adresse du `UserData` de chaque
	// asteroide, et un vector qui grandit deplace ses elements.
	std::vector<std::unique_ptr<Asteroid>> asteroids_;
	b2WorldId world_;
};
